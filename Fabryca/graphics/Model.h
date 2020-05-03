#pragma once

#include "Foundation.h"
#include "Vertex.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "SceneObject.h"

#include <vector>
#include <glm/glm.hpp>


class Model: public SceneObject {
public:
    Model(
        const std::string& meshFilepath,
        const std::string& textureFilepath,
        const std::string& shaderFilepath
    );
    Model(
        const Mesh& mesh,
        const Texture& texture,
        const Shader& shader
    );
    ~Model();


    const Mesh& mesh() const;
    const Texture& texture() const;
    const Shader& shader() const;
    const VertexArray& vertexArray() const;
    const VertexBuffer& vertexBuffer() const;

    glm::mat4 modelMatrix() const;

    Void setMesh(const std::string& filepath);
    Void setTexture(const std::string& filepath);
    Void setShader(const std::string& filepath);

private:
    const Bool _sharesMesh;
    const Bool _sharesTexture;
    const Bool _sharesShader;

    const Mesh* _mesh;
    const Texture* _texture;
    const Shader* _shader;
};
