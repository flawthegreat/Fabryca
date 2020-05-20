#include "VertexBuffer.h"
#include "graphics/glad.h"

#include <type_traits>


std::unordered_map<UInt, UInt> VertexBuffer::_referenceCount;

VertexBuffer::VertexBuffer():
    _dataSize(0),
    _attributeCount(0)
{
    glGenVertexArrays(1, &_vertexArray);
    glGenBuffers(1, &_id);

    ++_referenceCount[_id];
}

VertexBuffer::VertexBuffer(const Void* data, UInt dataSize):
    _dataSize(dataSize),
    _attributeCount(0)
{
    glGenVertexArrays(1, &_vertexArray);
    glGenBuffers(1, &_id);

    glBindBuffer(GL_COPY_WRITE_BUFFER, _id);
    glBufferData(GL_COPY_WRITE_BUFFER, _dataSize, data, GL_STATIC_DRAW);

    ++_referenceCount[_id];
}

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer):
    _id(vertexBuffer._id),
    _dataSize(vertexBuffer._dataSize),
    _vertexArray(vertexBuffer._vertexArray),
    _attributeCount(vertexBuffer._attributeCount)
{
    ++_referenceCount[_id];
}

VertexBuffer& VertexBuffer::operator= (const VertexBuffer& vertexBuffer) {
    if (this == &vertexBuffer) return *this;

    this->~VertexBuffer();

    _id = vertexBuffer._id;
    _dataSize = vertexBuffer._dataSize;
    _vertexArray = vertexBuffer._vertexArray;
    _attributeCount = vertexBuffer._attributeCount;

    ++_referenceCount[_id];

    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer):
    _id(vertexBuffer._id),
    _dataSize(vertexBuffer._dataSize),
    _vertexArray(vertexBuffer._vertexArray),
    _attributeCount(vertexBuffer._attributeCount)
{
    ++_referenceCount[_id];
}

VertexBuffer& VertexBuffer::operator= (VertexBuffer&& vertexBuffer) {
    if (this == &vertexBuffer) return *this;
    
    this->~VertexBuffer();

    _id = vertexBuffer._id;
    _dataSize = vertexBuffer._dataSize;
    _vertexArray = vertexBuffer._vertexArray;
    _attributeCount = vertexBuffer._attributeCount;

    ++_referenceCount[_id];

    return *this;
}

VertexBuffer::~VertexBuffer() {
    --_referenceCount[_id];

    if (_referenceCount[_id] == 0) {
        glDeleteBuffers(1, &_id);
        glDeleteVertexArrays(1, &_vertexArray);
    }
}

UInt VertexBuffer::id() const {
    return _id;
}

UInt VertexBuffer::dataSize() const {
    return _dataSize;
}

Void VertexBuffer::bind() const {
    glBindVertexArray(_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

Void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Void VertexBuffer::applyLayout(const Layout& layout) {
    bind();

    const std::vector<Layout::Attribute>& attributes = layout.attributes();

    UInt offset = 0;
    const UInt attributeCount = _attributeCount;
    for (UInt i = attributeCount; i < attributeCount + attributes.size(); ++i) {
        const Layout::Attribute& attribute = attributes[i - attributeCount];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            attribute.count,
            attribute.type,
            attribute.normalized,
            layout.stride(),
            reinterpret_cast<const Void*>(offset)
        );

        offset += attribute.count * attribute.typeSize;

        ++_attributeCount;
    }
}


VertexBuffer::Layout::Layout():
    _attributes(),
    _stride(0)
{}

const std::vector<VertexBuffer::Layout::Attribute>& VertexBuffer::Layout::attributes() const {
    return _attributes;
}

UInt VertexBuffer::Layout::stride() const {
    return _stride;
}

template<typename Type>
Void VertexBuffer::Layout::appendAttribute(UInt count, Bool normalized) {
    constexpr Int glType = []() {
        if constexpr (std::is_same<Type, Float>::value) {
            return GL_FLOAT;
        } else if (std::is_same<Type, UInt>::value) {
            return GL_UNSIGNED_INT;
        } else if (std::is_same<Type, Byte>::value) {
            return GL_UNSIGNED_BYTE;
        } else {
            static_assert(std::is_same<Type, Byte>::value, "Unknown attribute type.");
        }
    }();

    _attributes.emplace_back(glType, sizeof(Type), count, normalized);
    _stride += count * _attributes.back().typeSize;
}

template<>
Void VertexBuffer::Layout::appendAttribute<Vertex>(UInt count, Bool normalized) {
    for (Int i = 0; i < static_cast<Int>(count); ++i) {
        appendAttribute<Float>(3, normalized);
        appendAttribute<Float>(2, normalized);
        appendAttribute<Float>(3, normalized);
    }
}


VertexBuffer::Layout::Attribute::Attribute(UInt type, UInt typeSize, UInt count, Bool normalized):
    type(type),
    typeSize(typeSize),
    count(count),
    normalized(static_cast<Byte>(normalized ? GL_TRUE : GL_FALSE))
{}
