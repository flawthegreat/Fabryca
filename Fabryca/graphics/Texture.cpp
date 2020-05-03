#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <cmath>
#include <stdexcept>
#include <vector>


Texture::Texture(const std::string& filepath): _isOpaque(true) {
    FILE* file = fopen(filepath.c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << filepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read texture data.");
    }

    fseek(file, 0, SEEK_END);
    Int size = static_cast<Int>(ftell(file)) - 2;

    std::vector<Byte> rawData(size);

    UInt width = 0;
    rewind(file);
    fread(&width, 2, 1, file);
    UInt height = size / width;

    fread(&rawData[0], 1, size, file);
    fclose(file);

    Byte* data = new Byte[size * 4];

    Byte r = 0;
    Byte g = 0;
    Byte b = 0;
    Byte a = 0;

    for (int i = 0; i < rawData.size(); ++i) {
        if (rawData[i] <= 100) {
            r = g = b = static_cast<Byte>(static_cast<Double>(rawData[i]) / 100.0 * 255.0);
            a = 255;
        } else if (rawData[i] == 101) {
            r = a = 255;
            g = b = 0;
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

	glGenTextures(1, &_id);
	bind();

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    delete[] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(Texture&& texture): _id(texture._id), _isOpaque(texture._isOpaque) {
    bind();

    texture._id = 0;
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
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

Texture& Texture::operator= (Texture&& texture) {
    glDeleteTextures(1, &_id);

    _id = texture._id;
    _isOpaque = texture._isOpaque;
    bind();

    texture._id = 0;

    return *this;
}
