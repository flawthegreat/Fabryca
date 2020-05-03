#include "Shader.h"

#include <glad/glad.h>
#include <cstdio>
#include <iostream>
#include <stdexcept>


enum class Shader::Type {
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER
};


Shader::Shader(const std::string& filepath): _id(glCreateProgram()) {
    std::string vertexSource;
    std::string fragmentSource;
    _readSourceIntoString(filepath + "/vertex.glsl", vertexSource);
    _readSourceIntoString(filepath + "/fragment.glsl", fragmentSource);

    UInt vertexShader = _compileSource(Type::vertex, vertexSource);
    UInt fragmentShader = _compileSource(Type::fragment, fragmentSource);

    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);
    glValidateProgram(_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(Shader&& shader):
    _id(shader._id),
    _uniformLocationCache(shader._uniformLocationCache)
{
    shader._id = 0;
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

Void Shader::setUniform1i(const std::string& name, Int value) const {
    glUniform1i(_uniformLocation(name), value);
}

Void Shader::setUniform1f(const std::string& name, Float value) const {
    glUniform1f(_uniformLocation(name), value);
}

Void Shader::setUniform2f(const std::string& name, const glm::vec2& vector) const {
    glUniform2f(_uniformLocation(name), vector[0], vector[1]);
}

Void Shader::setUniform3f(const std::string& name, const glm::vec3& vector) const {
    glUniform3f(_uniformLocation(name), vector[0], vector[1], vector[2]);
}

Void Shader::setUniform4f(const std::string& name, const glm::vec4& vector) const {
    glUniform4f(_uniformLocation(name), vector[0], vector[1], vector[2], vector[3]);
}

Void Shader::setUniformMatrix4fv(
    const std::string& name,
    const glm::mat4& matrix,
    Bool transpose
) const {
    glUniformMatrix4fv(_uniformLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, &matrix[0][0]);
}

Void Shader::bind() const {
    glUseProgram(_id);
}

Void Shader::unbind() const {
    glUseProgram(0);
}

Shader& Shader::operator= (Shader&& shader) {
    glDeleteProgram(_id);

    _id = shader._id;
    _uniformLocationCache = shader._uniformLocationCache;

    shader._id = 0;

    return *this;
}

UInt Shader::_uniformLocation(const std::string& name) const {
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
        return _uniformLocationCache[name];
    }

    UInt location = glGetUniformLocation(_id, name.c_str());

    if (location == -1) {
        std::cerr << "Uniform \"" << name << "\" does not exist." << std::endl;
    }
    _uniformLocationCache[name] = location;

    return location;
}

Void Shader::_readSourceIntoString(const std::string& filepath, std::string& string) {
    FILE* file = fopen(filepath.c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << filepath << "\"." << std::endl;
        throw errno;
    }

    fseek(file, 0, SEEK_END);
    string.resize(ftell(file));
    rewind(file);
    fread(&string[0], 1, string.size(), file);
    fclose(file);
}

UInt Shader::_compileSource(Type type, const std::string& source) {
    UInt id = glCreateShader(static_cast<GLenum>(type));
    const Char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    Int successful = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &successful);
    if (!successful) {
        Int messageLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &messageLength);
        Char* message = new Char[messageLength];
        glGetShaderInfoLog(id, messageLength, &messageLength, message);

        std::cerr << "Shader compilation error:" << std::endl << message;
        std::cerr << "source:" << std::endl << source << std::endl;

        delete[] message;
        glDeleteShader(id);

        return 0;
    }

    return id;
}
