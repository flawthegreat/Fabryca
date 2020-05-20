#include "Animation.h"


Animation::Animation(
    Type type,
    SceneObject& object,
    const glm::vec3& newValue,
    Double duration,
    const std::function<Void (Bool)>& callback
):
    type(type),
    object(&object),
    newValue(newValue),
    timeLeft(duration),
    lastStepTime(),
    callback(callback)
{}
