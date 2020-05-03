#pragma once

#include "Foundation.h"

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>


class Shader {
public:
    Shader(const std::string& filepath);
    Shader(const Shader&) = delete;
    Shader(Shader&& shader);
    ~Shader();


    Void setUniform1i(const std::string& name, Int value) const;

    Void setUniform1f(const std::string& name, Float value) const;
    Void setUniform2f(const std::string& name, const glm::vec2& vector) const;
    Void setUniform3f(const std::string& name, const glm::vec3& vector) const;
    Void setUniform4f(const std::string& name, const glm::vec4& vector) const;

    Void setUniformMatrix4fv(
        const std::string& name,
        const glm::mat4& matrix,
        Bool transpose = false
    ) const;

    Void bind() const;
    Void unbind() const;

    Shader& operator= (const Shader&) = delete;
    Shader& operator= (Shader&& shader);

private:
    enum class Type;


    UInt _id;
    mutable std::unordered_map<std::string, UInt> _uniformLocationCache;


    UInt _uniformLocation(const std::string& name) const;

    static Void _readSourceIntoString(const std::string& filepath, std::string& string);
    static UInt _compileSource(Type type, const std::string& source);
};
