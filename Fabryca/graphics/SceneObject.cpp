#include "SceneObject.h"
#include "Renderer.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


SceneObject::SceneObject():
    _position(0.0f),
    _rotation(0.0f),
    _scale(1.0f),
    _positionMatrix(1.0f),
    _rotationMatrix(1.0f),
    _scaleMatrix(1.0f)
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

Void SceneObject::setPosition(const glm::vec3& position) {
    _position = position;

    _updatePositionMatrix();
}

Void SceneObject::setPosition(Float x, Float y, Float z) {
    setPosition({ x, y, z});
}

Void SceneObject::setXPosition(Float position) {
    _position.x = position;

    _updatePositionMatrix();
}

Void SceneObject::setYPosition(Float position) {
    _position.y = position;

    _updatePositionMatrix();
}

Void SceneObject::setZPosition(Float position) {
    _position.z = position;

    _updatePositionMatrix();
}

Void SceneObject::setXYPosition(const glm::vec2& position) {
    _position.x = position.x;
    _position.y = position.y;

    _updatePositionMatrix();
}

Void SceneObject::setXYPosition(Float x, Float y) {
    setXYPosition({ x, y });
}

Void SceneObject::setXZPosition(const glm::vec2& position) {
    _position.x = position.x;
    _position.z = position.y;

    _updatePositionMatrix();
}

Void SceneObject::setXZPosition(Float x, Float z) {
    setXZPosition({ x, z });
}

Void SceneObject::setYZPosition(const glm::vec2& position) {
    _position.y = position.x;
    _position.z = position.y;

    _updatePositionMatrix();
}

Void SceneObject::setYZPosition(Float y, Float z) {
    setYZPosition({ y, z });
}

Void SceneObject::setRotation(const glm::vec3& rotation) {
    _rotation = rotation;

    _updateRotationMatrix();
}

Void SceneObject::setRotation(Float x, Float y, Float z) {
    setRotation({ x, y, z });
}

Void SceneObject::setXRotation(Float rotation) {
    _rotation.x = rotation;

    _updateRotationMatrix();
}

Void SceneObject::setYRotation(Float rotation) {
    _rotation.y = rotation;

    _updateRotationMatrix();
}

Void SceneObject::setZRotation(Float rotation) {
    _rotation.z = rotation;

    _updateRotationMatrix();
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
    _scale.x = scale;

    _updateScaleMatrix();
}

Void SceneObject::setYScale(Float scale) {
    _scale.y = scale;

    _updateScaleMatrix();
}

Void SceneObject::setZScale(Float scale) {
    _scale.z = scale;

    _updateScaleMatrix();
}

Void SceneObject::moveTo(const glm::vec3& position, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        position,
        duration
    });
}

Void SceneObject::moveTo(Float x, Float y, Float z, Double duration) {
    moveTo({ x, y, z }, duration);
}

Void SceneObject::moveToX(Float x, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(x, _position.y, _position.z),
        duration
    });
}

Void SceneObject::moveToY(Float y, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, y, _position.z),
        duration
    });
}

Void SceneObject::moveToZ(Float z, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, _position.y, z),
        duration
    });
}

Void SceneObject::moveToXY(const glm::vec2& xy, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(xy.x, xy.y, _position.z),
        duration
    });
}

Void SceneObject::moveToXY(Float x, Float y, Double duration) {
    moveToXY({ x, y }, duration);
}

Void SceneObject::moveToXZ(const glm::vec2& xz, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(xz.x, _position.y, xz.y),
        duration
    });
}

Void SceneObject::moveToXZ(Float x, Float z, Double duration) {
    moveToXZ({ x, z }, duration);
}

Void SceneObject::moveToYZ(const glm::vec2& yz, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, yz.x, yz.y),
        duration
    });
}

Void SceneObject::moveToYZ(Float y, Float z, Double duration) {
    moveToYZ({ y, z }, duration);
}

Void SceneObject::moveBy(const glm::vec3& vector, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        _position + vector,
        duration
    });
}

Void SceneObject::moveBy(Float x, Float y, Float z, Double duration) {
    moveBy({ x, y, z }, duration);
}

Void SceneObject::moveByX(Float x, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x + x, _position.y, _position.z),
        duration
    });
}

Void SceneObject::moveByY(Float y, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, _position.y + y, _position.z),
        duration
    });
}

Void SceneObject::moveByZ(Float z, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, _position.y, _position.z + z),
        duration
    });
}

Void SceneObject::moveByXY(const glm::vec2& xy, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x + xy.x, _position.y + xy.y, _position.z),
        duration
    });
}

Void SceneObject::moveByXY(Float x, Float y, Double duration) {
    moveByXY({ x, y }, duration);
}

Void SceneObject::moveByXZ(const glm::vec2& xz, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x + xz.x, _position.y, _position.z + xz.y),
        duration
    });
}

Void SceneObject::moveByXZ(Float x, Float z, Double duration) {
    moveByXZ({ x, z }, duration);
}

Void SceneObject::moveByYZ(const glm::vec2& yz, Double duration) {
    Renderer::shared().appendAnimationToQueue({
        Animation::Type::move,
        this,
        glm::vec3(_position.x, _position.y + yz.x, _position.z + yz.y),
        duration
    });
}

Void SceneObject::moveByYZ(Float y, Float z, Double duration) {
    moveByYZ({ y, z }, duration);
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
