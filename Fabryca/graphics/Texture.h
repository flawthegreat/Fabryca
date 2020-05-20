#pragma once

#include "Foundation.h"
#include "utility/Filepath.h"

#include <string>
#include <unordered_map>


class Texture final {
public:
    Texture(const Filepath& filepath);
    Texture(const Texture& texture);
    Texture& operator= (const Texture& texture);
    Texture(Texture&& texture);
    Texture& operator= (Texture&& texture);
    ~Texture();


    UInt id() const;
    Bool isOpaque() const;

    Void bind() const;
    Void unbind() const;

private:
    UInt _id;
    Bool _isOpaque;

    static std::unordered_map<UInt, UInt> _referenceCount;


    Size _readIntoVector(const Filepath& filepath, std::vector<Byte>& data);
};
