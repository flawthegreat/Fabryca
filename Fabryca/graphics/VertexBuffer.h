#pragma once

#include "Foundation.h"
#include "Vertex.h"

#include <vector>
#include <glad/glad.h>


class VertexBuffer {
public:
    class Layout;


    VertexBuffer();
    VertexBuffer(const Void* data, UInt dataSize);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& vertexBuffer);
    ~VertexBuffer();


    UInt dataSize() const;

    Void bind() const;
    Void unbind() const;

    VertexBuffer& operator= (const VertexBuffer&) = delete;
    VertexBuffer& operator= (VertexBuffer&& vertexBuffer);

private:
    UInt _id;
    UInt _dataSize;
};


class VertexBuffer::Layout {
public:
    struct Attribute;


    Layout();


    const std::vector<Attribute>& attributes() const;
    UInt stride() const;

    template<typename T>
    Void appendAttribute(UInt count, Bool normalized = GL_FALSE);

    template<>
    Void appendAttribute<Float>(UInt count, Bool normalized);

    template<>
    Void appendAttribute<UInt>(UInt count, Bool normalized);

    template<>
    Void appendAttribute<Byte>(UInt count, Bool normalized);

    template<>
    Void appendAttribute<Vertex>(UInt count, Bool normalized);

private:
    std::vector<Attribute> _attributes;
    UInt _stride;
};


struct VertexBuffer::Layout::Attribute {
    UInt type;
    UInt typeSize;
    UInt count;
    Byte normalized;
};
