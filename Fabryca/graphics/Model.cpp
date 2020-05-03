#include "Model.h"
#include "Renderer.h"


Model::Model(
    const std::string& meshFilepath,
    const std::string& textureFilepath,
    const std::string& shaderFilepath
):
    _sharesMesh(false),
    _sharesTexture(false),
    _sharesShader(false),
    _mesh(new Mesh(meshFilepath)),
    _texture(new Texture(textureFilepath)),
    _shader(new Shader(shaderFilepath))
{}

Model::Model(
    const Mesh& mesh,
    const Texture& texture,
    const Shader& shader
):
    _sharesMesh(true),
    _sharesTexture(true),
    _sharesShader(true),
    _mesh(&mesh),
    _texture(&texture),
    _shader(&shader)
{}

Model::~Model() {
    if (!_sharesMesh) {
        delete _mesh;
    }
    if (!_sharesTexture) {
        delete _texture;
    }
    if (!_sharesShader) {
        delete _shader;
    }
}

const Mesh& Model::mesh() const {
    return *_mesh;
}

const Texture& Model::texture() const {
    return *_texture;
}

const Shader& Model::shader() const {
    return *_shader;
}

const VertexArray& Model::vertexArray() const {
    return _mesh->vertexArray();
}

const VertexBuffer& Model::vertexBuffer() const {
    return _mesh->vertexBuffer();
}

glm::mat4 Model::modelMatrix() const {
    return _positionMatrix * _rotationMatrix * _scaleMatrix;
}

Void Model::setMesh(const std::string& filepath) {
    if (!_sharesMesh) {
        delete _mesh;
    }

    _mesh = new Mesh(filepath);
}

Void Model::setTexture(const std::string& filepath) {
    if (!_sharesTexture) {
        delete _texture;
    }

    _texture = new Texture(filepath);
}

Void Model::setShader(const std::string& filepath) {
    if (!_sharesShader) {
        delete _shader;
    }

    _shader = new Shader(filepath);
}
