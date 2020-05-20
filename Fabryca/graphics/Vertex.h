#pragma once

#include "Foundation.h"

#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 position;
    glm::vec2 textureCoordinates;
    glm::vec3 normals;


    Vertex(
        const glm::vec3& position,
        const glm::vec2& textureCoordinates,
        const glm::vec3& normals
    );
};
