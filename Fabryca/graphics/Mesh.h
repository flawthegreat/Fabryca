#pragma once

#include "Foundation.h"
#include "VertexBuffer.h"

#include <string>


class Mesh final {
public:
    Mesh(const std::string& filepath);


    UInt vertexCount() const;
    const VertexBuffer& vertexBuffer() const;

private:
    VertexBuffer _vertexBuffer;


    Void _read(const std::string& filepath);
};
