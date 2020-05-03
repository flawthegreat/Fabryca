#include "Animation.h"


Animation::Animation(Type type, SceneObject* object, const glm::vec3& newValue, Double duration):
    type(type),
    object(object),
    newValue(newValue),
    timeLeft(duration),
    lastStepTime()
{}
