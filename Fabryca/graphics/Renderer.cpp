#include "Renderer.h"
#include "WindowManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <stdexcept>


Renderer* Renderer::_shared = nullptr;

Renderer& Renderer::shared() {
    if (!_shared) {
        _shared = new Renderer();

        WindowManager::shared().registerWindowSizeCallback(_windowSizeDidChange);
    }

    return *_shared;
}

Renderer::Renderer():
    _drawQueue(),
    _animationQueue(),
    _projectionMatrix(1.0f),
    _viewMatrix(1.0f),
    _lightPosition(0.0f, 1.0f, 0.0f),
    _lightDirection(0.0f, -1.0f, 0.0f),
    _lightPower(1.0f),
    _viewDistance(100),
    _camera()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer() {
    for (const Model* model: _drawQueue) {
        delete model;
    }
}

const std::deque<Model*>& Renderer::drawQueue() const {
    return _drawQueue;
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

Void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Void Renderer::draw(const Model& model) const {
    model.vertexArray().bind();

    model.shader().bind();
    glActiveTexture(GL_TEXTURE0);
    model.texture().bind();

    model.shader().setUniform1i("uTextureSampler", 0);
    model.shader().setUniformMatrix4fv("uModelMatrix", model.modelMatrix());
    model.shader().setUniformMatrix4fv("uViewMatrix", _viewMatrix);
    model.shader().setUniformMatrix4fv("uProjectionMatrix", _projectionMatrix);
    model.shader().setUniform3f("uLightPosition", _lightPosition);
    model.shader().setUniform3f("uLightDirection", _lightDirection);
    model.shader().setUniform1f("uLightPower", _lightPower);
    model.shader().setUniform1f("uViewDistance", _viewDistance);
    model.shader().setUniform3f("uWorldColor", clearColor());

    glDrawArrays(GL_TRIANGLES, 0, static_cast<UInt>(model.mesh().vertexCount()));
}

Void Renderer::drawModels() const {
    Renderer::shared().clear();

    for (const Model* model: _drawQueue) {
        draw(*model);
    }
}

Void Renderer::appendModelToDrawQueue(Model* model) {
    if (model->texture().isOpaque()) {
        _drawQueue.push_front(model);
    } else {
        _drawQueue.push_back(model);
    }
}

Void Renderer::removeModelFromDrawQueue(Model* model) {
    for (auto iterator = _drawQueue.begin(); iterator != _drawQueue.end(); ++iterator) {
        if (*iterator != model) continue;

        _drawQueue.erase(iterator);

        return;
    }
}

Void Renderer::processAnimations() {
    using namespace std::chrono;

    Time currentTime = high_resolution_clock::now();
    const glm::vec3& (SceneObject::*getValue)() const = nullptr;
    Void (SceneObject::*setValue)(const glm::vec3&) = nullptr;

    for (Animation& animation: _animationQueue) {
        if (animation.lastStepTime == invalidTime) {
            animation.lastStepTime = currentTime;
        }
        auto elapsedTime = duration_cast<nanoseconds>(currentTime - animation.lastStepTime).count();
        animation.lastStepTime = currentTime;

        Double timeSincePreviousCall = static_cast<Double>(elapsedTime) / 1'000'000'000.0;
        Float step = static_cast<Float>(timeSincePreviousCall / animation.timeLeft);
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
            removeAnimationFromQueue(animation);

            continue;
        }

        glm::vec3 valueDifference = (animation.newValue - (animation.object->*getValue)());
        glm::vec3 currentValue = (animation.object->*getValue)() + valueDifference * step;
        (animation.object->*setValue)(currentValue);

        if (dynamic_cast<Camera*>(animation.object)) {
            updateViewMatrix();
        }
    }
}

Void Renderer::appendAnimationToQueue(const Animation& animation) {
    removeAnimationFromQueue(animation.type, *animation.object);

    _animationQueue.push_back(animation);
}

Void Renderer::removeAnimationFromQueue(const Animation& animation) {
    for (auto iterator = _animationQueue.begin(); iterator != _animationQueue.end(); ++iterator) {
        if (&*iterator != &animation) continue;

        _animationQueue.erase(iterator);

        return;
    }
}

Void Renderer::removeAnimationFromQueue(Animation::Type type, const SceneObject& object) {
    for (auto iterator = _animationQueue.begin(); iterator != _animationQueue.end(); ++iterator) {
        if (iterator->type != type || iterator->object != &object) continue;

        _animationQueue.erase(iterator);

        return;
    }
}

Void Renderer::updateProjectionMatrix() {
    _projectionMatrix = glm::perspective(
        glm::radians(_camera.fieldOfView()),
        WindowManager::shared().windowAspectRatio(),
        0.1f,
        100.0f
    );
}

Void Renderer::updateProjectionMatrix(Int windowWidth, Int windowHeight) {
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
        glm::vec3(0, 1, 0)
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

Void Renderer::setCameraFieldOfView(Float fieldOfView) {
    _camera.setFieldOfView(fieldOfView);

    updateProjectionMatrix();
}

Void Renderer::setCameraPosition(const glm::vec3& position) {
    _camera.setPosition(position);

    updateViewMatrix();
}

Void Renderer::setCameraPosition(Float x, Float y, Float z) {
    _camera.setPosition(x, y, z);

    updateViewMatrix();
}

Void Renderer::setCameraFocusPoint(const glm::vec3& focusPoint) {
    _camera.setFocusPoint(focusPoint);

    updateViewMatrix();
}

Void Renderer::setCameraFocusPoint(Float x, Float y, Float z) {
    _camera.setFocusPoint(x, y, z);

    updateViewMatrix();
}

Void Renderer::moveCameraTo(glm::vec3 position, Double duration) {
    appendAnimationToQueue({
        Animation::Type::move,
        &_camera,
        position,
        duration
    });
}

Void Renderer::moveCameraTo(Float x, Float y, Float z, Double duration) {
    appendAnimationToQueue({
        Animation::Type::move,
        &_camera,
        glm::vec3(x, y, z),
        duration
    });
}

Void Renderer::setClearColor(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

Void Renderer::setClearColor(Float r, Float g, Float b) {
    glClearColor(r, g, b, 1.0f);
}

Void Renderer::_windowSizeDidChange(Int width, Int height) {
    _shared->updateProjectionMatrix();

    _shared->processAnimations();
    _shared->drawModels();
}
