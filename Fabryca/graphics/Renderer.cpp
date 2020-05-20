#include "Renderer.h"
#include "WindowManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <stdexcept>
#include <algorithm>


Renderer* Renderer::_shared = nullptr;

Renderer& Renderer::shared() {
    if (!_shared) { _shared = new Renderer(); }

    return *_shared;
}

Renderer::Renderer():
    _opaqueDrawQueue(),
    _transparentDrawQueue(),
    _animationQueue(),
    _projectionMatrix(1.0f),
    _viewMatrix(1.0f),
    _lightPosition(0.0f, 1.0f, 0.0f),
    _lightDirection(0.0f, -1.0f, 0.0f),
    _lightPower(1.0f),
    _viewDistance(100.0f),
    _camera(),
    _horizontalViewBounds(-1e10f, 1e10f, -1e10f, 1e10f)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

const std::vector<Animation>& Renderer::animationQueue() const {
    return _animationQueue;
}

const glm::mat4& Renderer::projectionMatrix() const {
    return _projectionMatrix;
}

const glm::mat4& Renderer::viewMatrix() const {
    return _viewMatrix;
}

const glm::vec3& Renderer::lightPosition() const {
    return _lightPosition;
}

const glm::vec3& Renderer::lightDirection() const {
    return _lightDirection;
}

Float Renderer::lightPower() const {
    return _lightPower;
}

Float Renderer::viewDistance() const {
    return _viewDistance;
}

const Camera& Renderer::camera() const {
    return _camera;
}

glm::vec3 Renderer::clearColor() const {
    glm::vec3 color;
    glGetFloatv(GL_COLOR_CLEAR_VALUE, &color[0]);

    return color;
}

const glm::vec4& Renderer::horizontalViewBounds() const {
    return _horizontalViewBounds;
}

Void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Void Renderer::draw() const {
    Renderer::shared().clear();

    for (const auto& model: _opaqueDrawQueue) { _drawModel(*model); }
    for (const auto& [priority, model]: _transparentDrawQueue) { _drawModel(*model); }
}

Void Renderer::addModelToDrawQueue(const Model& model, Int priority) {
    assert(priority >= 0);

    if (model.texture.isOpaque()) {
        _opaqueDrawQueue.emplace_back(&model);

        return;
    }

    priority += IntMin;

    const std::pair<Int, const Model*> element = { priority, &model };
    _transparentDrawQueue.insert(std::lower_bound(
        _transparentDrawQueue.rbegin(),
        _transparentDrawQueue.rend(),
        element
    ).base(), element);
}

Void Renderer::removeModelFromDrawQueue(const Model& model) {
    if (model.texture.isOpaque()) {
        for (auto itr = _opaqueDrawQueue.begin(); itr != _opaqueDrawQueue.end(); ++itr) {
            if (*itr != &model) continue;

            _opaqueDrawQueue.erase(itr);

            return;
        }
    }

    for (auto itr = _transparentDrawQueue.begin(); itr != _transparentDrawQueue.end(); ++itr) {
        if (itr->second != &model) continue;

        _transparentDrawQueue.erase(itr);

        return;
    }
}

Void Renderer::clearDrawQueue() {
    _opaqueDrawQueue.clear();
    _transparentDrawQueue.clear();
}

Void Renderer::processAnimations() {
    using namespace std::chrono;

    const Time currentTime = high_resolution_clock::now();

    Double timeSincePreviousCall = 0.0;
    Float step = 0.0;

    glm::vec3 stepValue;

    const glm::vec3& (SceneObject::*getValue)() const = nullptr;
    Void (SceneObject::*setValue)(const glm::vec3&) = nullptr;

    for (Animation& animation: _animationQueue) {
        if (animation.lastStepTime == invalidTime) {
            animation.lastStepTime = currentTime;
        }
        timeSincePreviousCall = static_cast<Double>(
            duration_cast<nanoseconds>(currentTime - animation.lastStepTime).count()
        ) / 1'000'000'000.0;
        animation.lastStepTime = currentTime;

        step = static_cast<Float>(timeSincePreviousCall / animation.timeLeft);
        animation.timeLeft -= timeSincePreviousCall;

        switch (animation.type) {
        case Animation::Type::move:
            getValue = &SceneObject::position;
            setValue = &SceneObject::setPosition;
            break;
        case Animation::Type::rotate:
            getValue = &SceneObject::rotation;
            setValue = &SceneObject::setRotation;
            break;
        case Animation::Type::scale:
            getValue = &SceneObject::scale;
            setValue = &SceneObject::setScale;
            break;
        default:
            throw std::runtime_error("Unknown animation type.");
        }

        if (animation.timeLeft <= 0.0) {
            (animation.object->*setValue)(animation.newValue);

            continue;
        }

        stepValue = animation.newValue + (step - 1.0f) *
            (animation.newValue - (animation.object->*getValue)());
        (animation.object->*setValue)(stepValue);

        if (dynamic_cast<Camera*>(animation.object)) {
            updateViewMatrix();
        }
    }

    for (Int i = static_cast<Int>(_animationQueue.size()) - 1; i >= 0; --i) {
        if (_animationQueue[i].timeLeft > 0.0) continue;

        Callback callback = _animationQueue[i].callback;
        _animationQueue.erase(_animationQueue.begin() + i);
        if (callback) { callback(true); }
    }
}

Void Renderer::addAnimationToQueue(
    Animation::Type type,
    SceneObject& object,
    const glm::vec3& newValue,
    Double duration,
    const Callback& callback
) {
    for (Animation& _animation: _animationQueue) {
        if (_animation.type != type || _animation.object != &object) continue;

        auto _callback = _animation.callback;
        _animation = Animation(type, object, newValue, duration, callback);
        if (_callback) { _callback(false); }

        return;
    }

    _animationQueue.emplace_back(type, object, newValue, duration, callback);
}

Void Renderer::addAnimationToQueue(const Animation& animation) {
    for (Animation& _animation: _animationQueue) {
        if (_animation.type != animation.type || _animation.object != animation.object) continue;

        Callback callback = _animation.callback;
        _animation = animation;
        if (callback) { callback(false); }

        return;
    }

    _animationQueue.emplace_back(animation);
}

Void Renderer::removeAnimationFromQueue(const Animation& animation) {
    for (auto itr = _animationQueue.begin(); itr != _animationQueue.end(); ++itr) {
        if (itr->type != animation.type || itr->object != animation.object) continue;

        Callback callback = itr->callback;
        _animationQueue.erase(itr);
        if (callback) { callback(false); }

        return;
    }
}

Void Renderer::removeAnimationsForModel(const Model& model) {
    for (Int i = static_cast<Int>(_animationQueue.size()) - 1; i >= 0; --i) {
        if (_animationQueue[i].object != &model) continue;

        Callback callback = _animationQueue[i].callback;
        _animationQueue.erase(_animationQueue.begin() + i);
        if (callback) { callback(false); }
    }
}

Void Renderer::clearAnimationQueue() {
    _animationQueue.clear();
}

Void Renderer::updateProjectionMatrix() {
    _projectionMatrix = glm::perspective(
        glm::radians(_camera.fieldOfView()),
        WindowManager::shared().windowAspectRatio(),
        0.1f,
        100.0f
    );
}

Void Renderer::updateViewMatrix() {
    _viewMatrix = glm::lookAt(
        _camera.position(),
        _camera.focusPoint(),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

Void Renderer::setLightPosition(const glm::vec3& position) {
    _lightPosition = position;
}

Void Renderer::setLightPosition(Float x, Float y, Float z) {
    setLightPosition({ x, y, z });
}

Void Renderer::setLightDirection(const glm::vec3& direction) {
    _lightDirection = direction;
}

Void Renderer::setLightDirection(Float x, Float y, Float z) {
    setLightDirection({ x, y, z });
}

Void Renderer::setLightPower(Float power) {
    _lightPower = power;
}

Void Renderer::setViewDistance(Float viewDistance) {
    _viewDistance = viewDistance;
}

Void Renderer::setHorizontalViewBounds(const glm::vec4& bounds) {
    _horizontalViewBounds = bounds;
}

Void Renderer::setHorizontalViewBounds(Float minX, Float maxX, Float minY, Float maxY) {
    setHorizontalViewBounds({ minX, maxX, minY, maxY });
}

Void Renderer::setClearColor(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

Void Renderer::setClearColor(Float r, Float g, Float b) {
    setClearColor({ r, g, b });
}

Void Renderer::setCameraFieldOfView(Float fieldOfView) {
    _camera.setFieldOfView(fieldOfView);

    updateProjectionMatrix();
}

Void Renderer::setCameraPosition(const glm::vec3& position) {
    _camera.setPosition(position);

    updateViewMatrix();
}

Void Renderer::setCameraPosition(Float x, Float y, Float z) {
    setCameraPosition({ x, y, z });
}

Void Renderer::setCameraFocusPoint(const glm::vec3& focusPoint) {
    _camera.setFocusPoint(focusPoint);

    updateViewMatrix();
}

Void Renderer::setCameraFocusPoint(Float x, Float y, Float z) {
    setCameraFocusPoint({ x, y, z });
}

Void Renderer::moveCameraTo(
    const glm::vec3& position,
    Double duration,
    const Callback& callback
) {
    addAnimationToQueue(Animation::Type::move, _camera, position, duration, callback);
}

Void Renderer::moveCameraTo(
    Float x,
    Float y,
    Float z,
    Double duration,
    const Callback& callback
) {
    moveCameraTo({ x, y, z }, duration, callback);
}

Void Renderer::_drawModel(const Model& model) const {
    model.mesh.vertexBuffer().bind();
    model.shader.bind();
    glActiveTexture(GL_TEXTURE0);
    model.texture.bind();

    model.shader.setUniform("uTextureSampler", 0);
    model.shader.setUniform("uModelMatrix", model.modelMatrix());
    model.shader.setUniform("uViewMatrix", _viewMatrix);
    model.shader.setUniform("uProjectionMatrix", _projectionMatrix);
    model.shader.setUniform("uLightPosition", _lightPosition);
    model.shader.setUniform("uLightDirection", _lightDirection);
    model.shader.setUniform("uLightPower", _lightPower);
    model.shader.setUniform("uViewDistance", _viewDistance);
    model.shader.setUniform("uWorldColor", clearColor());
    model.shader.setUniform("uHorizontalViewBounds", _horizontalViewBounds);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<UInt>(model.mesh.vertexCount()));
}
