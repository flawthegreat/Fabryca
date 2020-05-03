#pragma once

#include "Foundation.h"
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <chrono>

using Time = std::chrono::high_resolution_clock::time_point;
const Time invalidTime = Time();


struct Animation {
    enum class Type {
        move,
        rotate,
        scale
    };


    Type type;
    SceneObject* object;
    glm::vec3 newValue;
    Double timeLeft;
    Time lastStepTime;


    Animation(Type type, SceneObject* object, const glm::vec3& newValue, Double duration);
};
