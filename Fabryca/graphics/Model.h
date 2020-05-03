#pragma once

#include "Foundation.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "SceneObject.h"

#include <vector>
#include <glm/glm.hpp>


struct Model final: public SceneObject {
    Mesh mesh;
    Texture texture;
    Shader shader;


    Model(
        const std::string& meshFilepath,
        const std::string& textureFilepath,
        const std::string& shaderFilepath
    );
    Model(const Mesh& mesh, const Texture& texture, const Shader& shader);


    glm::mat4 modelMatrix() const;
};
