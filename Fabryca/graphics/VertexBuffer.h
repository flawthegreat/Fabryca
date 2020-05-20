#pragma once

#include "Foundation.h"
#include "Vertex.h"

#include <vector>
#include <unordered_map>


class VertexBuffer final {
public:
    class Layout;


    VertexBuffer();
    VertexBuffer(const Void* data, UInt dataSize);

    VertexBuffer(const VertexBuffer& vertexBuffer);
    VertexBuffer& operator= (const VertexBuffer& vertexBuffer);
    VertexBuffer(VertexBuffer&& vertexBuffer);
    VertexBuffer& operator= (VertexBuffer&& vertexBuffer);
    
    ~VertexBuffer();


    UInt id() const;
    UInt dataSize() const;

    Void bind() const;
    Void unbind() const;

    Void applyLayout(const Layout& layout);

private:
    UInt _id;
    UInt _dataSize;
    UInt _vertexArray;
    UInt _attributeCount;

    static std::unordered_map<UInt, UInt> _referenceCount;
};


class VertexBuffer::Layout {
public:
    struct Attribute;


    Layout();


    const std::vector<Attribute>& attributes() const;
    UInt stride() const;

    template<typename Type>
    Void appendAttribute(UInt count, Bool normalized = false);

private:
    std::vector<Attribute> _attributes;
    UInt _stride;
};


struct VertexBuffer::Layout::Attribute {
    UInt type;
    UInt typeSize;
    UInt count;
    Byte normalized;


    Attribute(UInt type, UInt typeSize, UInt count, Bool normalized);
};
