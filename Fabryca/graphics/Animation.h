#pragma once

#include "Foundation.h"
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <chrono>

using Time = std::chrono::high_resolution_clock::time_point;
const Time invalidTime = Time();


struct Animation final {
    enum class Type;


    Type type;
    SceneObject* object;
    glm::vec3 newValue;
    Double timeLeft;
    Time lastStepTime;
    std::function<Void (Bool)> callback;


    Animation(
        Type type,
        SceneObject& object,
        const glm::vec3& newValue,
        Double duration,
        const std::function<Void (Bool)>& callback = std::function<Void (Bool)>()
    );
};


enum class Animation::Type {
    move,
    rotate,
    scale
};
