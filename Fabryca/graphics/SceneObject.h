#pragma once

#include "Foundation.h"

#include <functional>
#include <glm/glm.hpp>
#include <vector>


class SceneObject {
public:
    SceneObject();
    virtual ~SceneObject() {};


    const glm::vec3& position() const;
    const glm::vec3& rotation() const;
    const glm::vec3& scale() const;
    glm::vec3 localPosition() const;
    glm::vec3 localRotation() const;
    const SceneObject* parent() const;
    const std::vector<SceneObject*>& children() const;

    Void addChild(SceneObject* object);
    Void removeChild(SceneObject* object);

    Void setPosition(const glm::vec3& position);
    Void setPosition(Float x, Float y, Float z);
    Void setXPosition(Float position);
    Void setYPosition(Float position);
    Void setZPosition(Float position);
    Void setXYPosition(const glm::vec2& position);
    Void setXYPosition(Float x, Float y);
    Void setXZPosition(const glm::vec2& position);
    Void setXZPosition(Float x, Float z);
    Void setYZPosition(const glm::vec2& position);
    Void setYZPosition(Float y, Float z);

    Void setRotation(const glm::vec3& rotation);
    Void setRotation(Float x, Float y, Float z);
    Void setXRotation(Float rotation);
    Void setYRotation(Float rotation);
    Void setZRotation(Float rotation);

    Void setScale(const glm::vec3& scale);
    Void setScale(Float x, Float y, Float z);
    Void setScale(Float scale);
    Void setXScale(Float scale);
    Void setYScale(Float scale);
    Void setZScale(Float scale);

    Void moveTo(
        const glm::vec3& position,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveTo(
        Float x,
        Float y,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToX(
        Float x,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToY(
        Float y,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToZ(
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToXY(
        const glm::vec2& xy,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToXY(
        Float x,
        Float y,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToXZ(
        const glm::vec2& xz,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToXZ(
        Float x,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToYZ(
        const glm::vec2& yz,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveToYZ(
        Float y,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );

    Void moveBy(
        const glm::vec3& vector,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveBy(
        Float x,
        Float y,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByX(
        Float x,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByY(
        Float y,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByZ(
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByXY(
        const glm::vec2& xy,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByXY(
        Float x,
        Float y,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByXZ(
        const glm::vec2& xz,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByXZ(
        Float x,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByYZ(
        const glm::vec2& yz,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
    Void moveByYZ(
        Float y,
        Float z,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );

protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _positionMatrix;
    glm::mat4 _rotationMatrix;
    glm::mat4 _scaleMatrix;

    SceneObject* _parent;
    std::vector<SceneObject*> _children;


    Void _updatePositionMatrix();
    Void _updateRotationMatrix();
    Void _updateScaleMatrix();
};
