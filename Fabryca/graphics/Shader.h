#pragma once

#include "Foundation.h"
#include "utility/Filepath.h"

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>


class Shader final {
public:
    Shader(const Filepath& filepath);

    Shader(const Shader& shader);
    Shader& operator= (const Shader& shader);
    Shader(Shader&& shader);
    Shader& operator= (Shader&& shader);
    
    ~Shader();


    Void setUniform(const std::string& name, Int value) const;

    Void setUniform(const std::string& name, Float value) const;
    Void setUniform(const std::string& name, const glm::vec2& vector) const;
    Void setUniform(const std::string& name, const glm::vec3& vector) const;
    Void setUniform(const std::string& name, const glm::vec4& vector) const;

    Void setUniform(const std::string& name, const glm::mat4& matrix, Bool transpose = false) const;

    Void bind() const;
    Void unbind() const;

private:
    enum class Type;


    UInt _id;
    mutable std::unordered_map<std::string, UInt> _uniformLocationCache;

    static std::unordered_map<UInt, UInt> _referenceCount;


    UInt _uniformLocation(const std::string& name) const;

    static Void _readSourceIntoString(const Filepath& filepath, std::string& string);
    static UInt _compileSource(Type type, const std::string& source);
};
