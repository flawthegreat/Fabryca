#include "Texture.h"
#include "graphics/glad.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>


std::unordered_map<UInt, UInt> Texture::_referenceCount;

Texture::Texture(const Filepath& filepath):
    _isOpaque(true)
{
    std::vector<Byte> data;
    const auto [width, height] = _readIntoVector(filepath, data);

	glGenTextures(1, &_id);
	bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    ++_referenceCount[_id];
}

Texture::Texture(const Texture& texture):
    _id(texture._id),
    _isOpaque(texture._isOpaque)
{
    ++_referenceCount[_id];
}

Texture& Texture::operator= (const Texture& texture) {
    if (this == &texture) return *this;

    this->~Texture();

    _id = texture._id;
    _isOpaque = texture._isOpaque;

    ++_referenceCount[_id];

    return *this;
}

Texture::Texture(Texture&& texture):
    _id(texture._id),
    _isOpaque(texture._isOpaque)
{
    ++_referenceCount[_id];
}

Texture& Texture::operator= (Texture&& texture) {
    if (this == &texture) return *this;

    this->~Texture();

    _id = texture._id;
    _isOpaque = texture._isOpaque;

    ++_referenceCount[_id];

    return *this;
}

Texture::~Texture() {
    --_referenceCount[_id];

    if (_referenceCount[_id] == 0) {
        glDeleteTextures(1, &_id);
    }
}

UInt Texture::id() const {
    return _id;
}

Bool Texture::isOpaque() const {
    return _isOpaque;
}

Void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, _id);
}

Void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Size Texture::_readIntoVector(const Filepath& filepath, std::vector<Byte>& data) {
    FILE* file = fopen(filepath.stringValue().c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << filepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read texture data.");
    }

    fseek(file, 0, SEEK_END);
    const Int size = static_cast<Int>(ftell(file)) - 2;

    std::vector<Byte> rawData(size);

    UInt16 width;
    rewind(file);
    fread(&width, 2, 1, file);
    const UInt16 height = size / width;

    fread(&rawData[0], 1, size, file);
    fclose(file);

    data.resize(size * 4);

    Byte r = 0;
    Byte g = 0;
    Byte b = 0;
    Byte a = 0;

    for (Int i = 0; i < static_cast<Int>(rawData.size()); ++i) {
        if (rawData[i] <= 100) {
            r = g = b = static_cast<Byte>(static_cast<Double>(rawData[i]) * 255.0 / 100.0);
            a = 255;
        } else if (rawData[i] == 101) {
            r = a = 255;
            g = b = 0;
        } else if (rawData[i] == 102) {
            r = 144;
            g = b = 0;
            a = 255;
        } else if (rawData[i] == 255) {
            r = g = b = a = 0;
            _isOpaque = false;
        } else {
            throw std::runtime_error("Unknown texture format.");
        }

        data[i * 4 + 0] = r;
        data[i * 4 + 1] = g;
        data[i * 4 + 2] = b;
        data[i * 4 + 3] = a;
    }

    return { static_cast<Int>(width), static_cast<Int>(height) };
}
