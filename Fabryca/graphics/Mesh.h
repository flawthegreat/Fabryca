#pragma once

#include "Foundation.h"
#include "VertexBuffer.h"
#include "utility/Filepath.h"

#include <string>


class Mesh final {
public:
    Mesh(const Filepath& filepath);


    UInt vertexCount() const;
    const VertexBuffer& vertexBuffer() const;

private:
    VertexBuffer _vertexBuffer;


    Void _read(const Filepath& filepath);
};
