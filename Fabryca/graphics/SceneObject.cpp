#include "SceneObject.h"
#include "Renderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


SceneObject::SceneObject():
    _position(0.0f),
    _rotation(0.0f),
    _scale(1.0f),
    _positionMatrix(1.0f),
    _rotationMatrix(1.0f),
    _scaleMatrix(1.0f),
    _parent(nullptr),
    _children()
{}

const glm::vec3& SceneObject::position() const {
    return _position;
}

const glm::vec3& SceneObject::rotation() const {
    return _rotation;
}

const glm::vec3& SceneObject::scale() const {
    return _scale;
}

glm::vec3 SceneObject::localPosition() const {
    return _parent ? _position - _parent->_position : _position;
}

glm::vec3 SceneObject::localRotation() const {
    return _parent ? _rotation - _parent->_rotation : _rotation;
}

const SceneObject* SceneObject::parent() const {
    return _parent;
}

const std::vector<SceneObject*>& SceneObject::children() const {
    return _children;
}

Void SceneObject::addChild(SceneObject* object) {
    if (object->_parent) {
        throw std::runtime_error("Object already has a parent.");
    }

    _children.emplace_back(object);
    object->_parent = this;
}

Void SceneObject::removeChild(SceneObject* object) {
    for (auto itr = _children.begin(); itr != _children.end(); ++itr) {
        if (*itr != object) continue;

        object->_parent = nullptr;
        _children.erase(itr);

        return;
    }
}

Void SceneObject::setPosition(const glm::vec3& position) {
    for (SceneObject* child: _children) {
        child->setPosition(child->localPosition() + position);
    }

    _position = position;

    _updatePositionMatrix();
}

Void SceneObject::setPosition(Float x, Float y, Float z) {
    setPosition({ x, y, z });
}

Void SceneObject::setXPosition(Float position) {
    setPosition({ position, _position.y, _position.z });
}

Void SceneObject::setYPosition(Float position) {
    setPosition({ _position.x, position, _position.z });
}

Void SceneObject::setZPosition(Float position) {
    setPosition({ _position.x, _position.y, position });
}

Void SceneObject::setXYPosition(const glm::vec2& position) {
    setPosition({ position.x, position.y, _position.z });
}

Void SceneObject::setXYPosition(Float x, Float y) {
    setXYPosition({ x, y });
}

Void SceneObject::setXZPosition(const glm::vec2& position) {
    setPosition({ position.x, _position.y, position.y });
}

Void SceneObject::setXZPosition(Float x, Float z) {
    setXZPosition({ x, z });
}

Void SceneObject::setYZPosition(const glm::vec2& position) {
    setPosition({ _position.x, position.x, position.y });
}

Void SceneObject::setYZPosition(Float y, Float z) {
    setYZPosition({ y, z });
}

Void SceneObject::setRotation(const glm::vec3& rotation) {
    for (SceneObject* child: _children) {
        child->setRotation(child->localRotation() + rotation);
    }

    _rotation = rotation;

    _updateRotationMatrix();
}

Void SceneObject::setRotation(Float x, Float y, Float z) {
    setRotation({ x, y, z });
}

Void SceneObject::setXRotation(Float rotation) {
    setRotation({ rotation, _rotation.y, _rotation.z });
}

Void SceneObject::setYRotation(Float rotation) {
    setRotation({ _rotation.x, rotation, _rotation.z });
}

Void SceneObject::setZRotation(Float rotation) {
    setRotation({ _rotation.x, _rotation.y, rotation });
}

Void SceneObject::setScale(const glm::vec3& scale) {
    _scale = scale;

    _updateScaleMatrix();
}

Void SceneObject::setScale(Float x, Float y, Float z) {
    setScale({ x, y, z });
}

Void SceneObject::setScale(Float scale) {
    setScale(glm::vec3(scale));
}

Void SceneObject::setXScale(Float scale) {
    setScale({ scale, _scale.y, _scale.z });
}

Void SceneObject::setYScale(Float scale) {
    setScale({ _scale.x, scale, _scale.z });
}

Void SceneObject::setZScale(Float scale) {
    setScale({ _scale.x, _scale.y, scale });
}

Void SceneObject::moveTo(
    const glm::vec3& position,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    Renderer::shared().addAnimationToQueue(
        Animation::Type::move,
        *this,
        position,
        duration,
        callback
    );
}

Void SceneObject::moveTo(
    Float x,
    Float y,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ x, y, z }, duration, callback);
}

Void SceneObject::moveToX(
    Float x,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ x, _position.y, _position.z }, duration, callback);
}

Void SceneObject::moveToY(
    Float y,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ _position.x, y, _position.z }, duration, callback);
}

Void SceneObject::moveToZ(
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ _position.x, _position.y, z }, duration, callback);
}

Void SceneObject::moveToXY(
    const glm::vec2& xy,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ xy.x, xy.y, _position.z }, duration, callback);
}

Void SceneObject::moveToXY(
    Float x,
    Float y,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveToXY({ x, y }, duration, callback);
}

Void SceneObject::moveToXZ(
    const glm::vec2& xz,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ xz.x, _position.y, xz.y }, duration, callback);
}

Void SceneObject::moveToXZ(
    Float x,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveToXZ({ x, z }, duration, callback);
}

Void SceneObject::moveToYZ(
    const glm::vec2& yz,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo({ _position.x, yz.x, yz.y }, duration, callback);
}

Void SceneObject::moveToYZ(
    Float y,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveToYZ({ y, z }, duration, callback);
}

Void SceneObject::moveBy(
    const glm::vec3& vector,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveTo(_position + vector, duration, callback);
}

Void SceneObject::moveBy(
    Float x,
    Float y,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ x, y, z }, duration, callback);
}

Void SceneObject::moveByX(
    Float x,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ x, 0.0f, 0.0f }, duration, callback);
}

Void SceneObject::moveByY(
    Float y,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ 0.0f, y, 0.0f }, duration, callback);
}

Void SceneObject::moveByZ(
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ 0.0f, 0.0f, z }, duration, callback);
}

Void SceneObject::moveByXY(
    const glm::vec2& xy,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ xy.x, xy.y, 0.0f }, duration, callback);
}

Void SceneObject::moveByXY(
    Float x,
    Float y,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveByXY({ x, y }, duration, callback);
}

Void SceneObject::moveByXZ(
    const glm::vec2& xz,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ xz.x, 0.0f, xz.y }, duration, callback);
}

Void SceneObject::moveByXZ(
    Float x,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveByXZ({ x, z }, duration, callback);
}

Void SceneObject::moveByYZ(
    const glm::vec2& yz,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveBy({ 0.0f, yz.x, yz.y }, duration, callback);
}

Void SceneObject::moveByYZ(
    Float y,
    Float z,
    Double duration,
    const std::function<Void (Bool)>& callback
) {
    moveByYZ({ y, z }, duration, callback);
}

Void SceneObject::_updatePositionMatrix() {
    _positionMatrix = glm::translate(glm::mat4(1.0f), _position);
}

Void SceneObject::_updateRotationMatrix() {
    _rotationMatrix = glm::rotate(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _rotationMatrix *= glm::rotate(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _rotationMatrix *= glm::rotate(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

Void SceneObject::_updateScaleMatrix() {
    _scaleMatrix = glm::scale(_scale);
}
