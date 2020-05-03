#pragma once

#include "Foundation.h"

#include <string>


class Texture {
public:
    Texture(const std::string& filepath);
    Texture(const Texture& texture) = delete;
    Texture(Texture&& texture);
    ~Texture();


    UInt id() const;
    Bool isOpaque() const;

    Void bind() const;
    Void unbind() const;

    Texture& operator= (const Texture& texture) = delete;
    Texture& operator= (Texture&& texture);

private:
    UInt _id;
    Bool _isOpaque;
};
