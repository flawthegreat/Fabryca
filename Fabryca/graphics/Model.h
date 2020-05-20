#pragma once

#include "Foundation.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "SceneObject.h"
#include "utility/Filepath.h"

#include <vector>
#include <glm/glm.hpp>


struct Model final: public SceneObject {
    Mesh mesh;
    Texture texture;
    Shader shader;


    Model(
        const Filepath& meshFilepath,
        const Filepath& textureFilepath,
        const Filepath& shaderFilepath
    );
    Model(const Mesh& mesh, const Texture& texture, const Shader& shader);


    glm::mat4 modelMatrix() const;
};
