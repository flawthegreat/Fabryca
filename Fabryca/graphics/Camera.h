#pragma once

#include "Foundation.h"
#include "SceneObject.h"


class Camera final: public SceneObject {
public:
    Camera();


    Float fieldOfView() const;
    const glm::vec3& focusPoint() const;

    Void setFieldOfView(Float fieldOfView);
    Void setFocusPoint(const glm::vec3& focusPoint);
    Void setFocusPoint(Float x, Float y, Float z);

private:
    Float _fieldOfView;
    glm::vec3 _focusPoint;
};
