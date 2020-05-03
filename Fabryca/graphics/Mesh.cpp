#include "Mesh.h"
#include "Vertex.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include <stdexcept>


Mesh::Mesh(const std::string& filepath) {
    _read(filepath);
}

UInt Mesh::vertexCount() const {
    return _vertexBuffer.dataSize() / sizeof(Vertex);
}

const VertexBuffer& Mesh::vertexBuffer() const {
    return _vertexBuffer;
}

Void Mesh::_read(const std::string& filepath) {
    FILE* file = fopen((resourcesPath + filepath).c_str(), "r");
	if (!file) {
        std::cerr << "Failed to open \"" << filepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read mesh data.");
	}

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<glm::vec3> normals;

    std::vector<Vertex> vertices;

    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    UInt vertexIndex[3], uvIndex[3], normalIndex[3];

    const auto abort = [&]() {
        std::cerr << "Failed to read \"" << filepath << "\"." << std::endl;
        throw std::runtime_error("Unexpected file format. Cannot read mesh data.");
    };

    Char lineHeader[128];
    Char stupidBuffer[128];
    while (fscanf(file, "%s", lineHeader) != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			if (fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z) != 3) abort();
			positions.emplace_back(position);
		} else if (strcmp(lineHeader, "vt") == 0) {
			if (fscanf(file, "%f %f\n", &uv.x, &uv.y) != 2) abort();
			textureCoordinates.emplace_back(uv);
		} else if (strcmp(lineHeader, "vn") == 0) {
			if (fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z) != 3) abort();
			normals.emplace_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
			if (fscanf(
                file,
                "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertexIndex[0],
                &uvIndex[0],
                &normalIndex[0],
                &vertexIndex[1],
                &uvIndex[1],
                &normalIndex[1],
                &vertexIndex[2],
                &uvIndex[2],
                &normalIndex[2]
            ) != 9) {
                abort();
			}

            vertices.emplace_back(
                positions[vertexIndex[0] - 1],
                textureCoordinates[uvIndex[0] - 1],
                normals[normalIndex[0] - 1]
            );
            vertices.emplace_back(
                positions[vertexIndex[1] - 1],
                textureCoordinates[uvIndex[1] - 1],
                normals[normalIndex[1] - 1]
            );
            vertices.emplace_back(
                positions[vertexIndex[2] - 1],
                textureCoordinates[uvIndex[2] - 1],
                normals[normalIndex[2] - 1]
            );
		} else {
			fgets(stupidBuffer, 128, file);
		}
	}

    fclose(file);

    _vertexBuffer = VertexBuffer(&vertices[0], static_cast<UInt>(vertices.size() * sizeof(Vertex)));

    VertexBuffer::Layout layout;
    layout.appendAttribute<Vertex>(1);

    _vertexBuffer.applyLayout(layout);
}
