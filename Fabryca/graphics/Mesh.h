#pragma once

#include "Foundation.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Vertex.h"

#include <string>
#include <vector>


class Mesh {
public:
    Mesh(const std::string& filepath);


    UInt vertexCount() const;
    const VertexArray& vertexArray() const;
    const VertexBuffer& vertexBuffer() const;

private:
    UInt _vertexCount;
    VertexArray _vertexArray;
    VertexBuffer _vertexBuffer;
};
