#include "Model.h"
#include "Renderer.h"


Model::Model(
    const Filepath& meshFilepath,
    const Filepath& textureFilepath,
    const Filepath& shaderFilepath
):
    mesh(meshFilepath),
    texture(textureFilepath),
    shader(shaderFilepath)
{}

Model::Model(const Mesh& mesh, const Texture& texture, const Shader& shader):
    mesh(mesh),
    texture(texture),
    shader(shader)
{}

glm::mat4 Model::modelMatrix() const {
    return _positionMatrix * _rotationMatrix * _scaleMatrix;
}
