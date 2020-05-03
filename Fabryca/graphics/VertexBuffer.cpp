#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(): _dataSize(0) {
    glGenBuffers(1, &_id);
}

VertexBuffer::VertexBuffer(const Void* data, UInt dataSize): _dataSize(dataSize) {
    glGenBuffers(1, &_id);
    bind();

    glBufferData(GL_ARRAY_BUFFER, _dataSize, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer):
    _id(vertexBuffer._id),
    _dataSize(vertexBuffer._dataSize)
{
    vertexBuffer._id = 0;
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_id);
}

UInt VertexBuffer::dataSize() const {
    return _dataSize;
}

Void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

Void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer& VertexBuffer::operator= (VertexBuffer&& vertexBuffer) {
    glDeleteBuffers(1, &_id);

    _id = vertexBuffer._id;
    _dataSize = vertexBuffer._dataSize;

    vertexBuffer._id = 0;

    return *this;
}


VertexBuffer::Layout::Layout(): _attributes(), _stride(0) {}

const std::vector<VertexBuffer::Layout::Attribute>& VertexBuffer::Layout::attributes() const {
    return _attributes;
}

UInt VertexBuffer::Layout::stride() const {
    return _stride;
}

template<>
Void VertexBuffer::Layout::appendAttribute<Float>(UInt count, Bool normalized) {
    _attributes.push_back({
        GL_FLOAT,
        sizeof(Float),
        count,
        static_cast<Byte>(normalized ? GL_TRUE : GL_FALSE)
    });
    _stride += count * _attributes.back().typeSize;
}

template<>
Void VertexBuffer::Layout::appendAttribute<UInt>(UInt count, Bool normalized) {
    _attributes.push_back({
        GL_UNSIGNED_INT,
        sizeof(UInt),
        count,
        static_cast<Byte>(normalized ? GL_TRUE : GL_FALSE)
    });
    _stride += count * _attributes.back().typeSize;
}

template<>
Void VertexBuffer::Layout::appendAttribute<Byte>(UInt count, Bool normalized) {
    _attributes.push_back({
        GL_UNSIGNED_BYTE,
        sizeof(Byte),
        count,
        static_cast<Byte>(normalized ? GL_TRUE : GL_FALSE)
    });
    _stride += count * _attributes.back().typeSize;
}

template<>
Void VertexBuffer::Layout::appendAttribute<Vertex>(UInt count, Bool normalized) {
    for (Int i = 0; i < count; ++i) {
        appendAttribute<Float>(3, normalized);
        appendAttribute<Float>(2, normalized);
        appendAttribute<Float>(3, normalized);
    }
}
