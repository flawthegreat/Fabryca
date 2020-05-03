#include "Camera.h"


Camera::Camera(): _fieldOfView(45.0f), _focusPoint(0.0f, 0.0f, 0.0f) {
    setPosition(0.0f, 0.0f, 1.0f);
}

Float Camera::fieldOfView() const {
    return _fieldOfView;
}

const glm::vec3& Camera::focusPoint() const {
    return _focusPoint;
}

Void Camera::setFieldOfView(Float fieldOfView) {
    _fieldOfView = fieldOfView;
}

Void Camera::setFocusPoint(const glm::vec3& focusPoint) {
    _focusPoint = focusPoint;
}

Void Camera::setFocusPoint(Float x, Float y, Float z) {
    _focusPoint = glm::vec3(x, y, z);
}
