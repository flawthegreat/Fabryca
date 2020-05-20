#include "graphics/Vertex.h"


Vertex::Vertex(
    const glm::vec3& position,
    const glm::vec2& textureCoordinates,
    const glm::vec3& normals
):
    position(position),
    textureCoordinates(textureCoordinates),
    normals(normals)
{}
