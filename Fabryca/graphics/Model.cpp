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

Model::~Model() {
    Renderer::shared().removeModelFromDrawQueue(*this);
    Renderer::shared().removeAnimationsForModel(*this);
}

glm::mat4 Model::modelMatrix() const {
    return _positionMatrix * _rotationMatrix * _scaleMatrix;
}

Void Model::show(Int priority) const {
    Renderer::shared().addModelToDrawQueue(*this, priority);
}

Void Model::hide() const {
    Renderer::shared().removeModelFromDrawQueue(*this);
}
