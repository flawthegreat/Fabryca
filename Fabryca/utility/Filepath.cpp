#include "utility/Filepath.h"


std::string Filepath::_rootFilepath = "";

Filepath::Filepath(const std::string& filepath):
    _filepath(filepath)
{
    _fixFormat(_filepath);
}

Filepath& Filepath::operator= (const std::string& filepath) {
    _filepath = filepath;
    _fixFormat(_filepath);

    return *this;
}

Filepath::Filepath(const Char* filepath):
    Filepath(std::string(filepath))
{}

Filepath& Filepath::operator= (const Char* filepath) {
    return *this = std::string(filepath);
}

std::string Filepath::stringValue() const {
    return _rootFilepath + _filepath;
}

Filepath::operator std::string () const {
    return stringValue();
}

Filepath& Filepath::operator+= (const Filepath& filepath) {
    _filepath += filepath._filepath;

    return *this;
}

const std::string& Filepath::rootFilepath() {
    return _rootFilepath;
}

Void Filepath::setRootFilepath(const std::string& newPath) {
    _rootFilepath = newPath;
    while (_rootFilepath.back() == '/') {
        _rootFilepath.pop_back();
    }
}

Void Filepath::_fixFormat(std::string& filepath) {
    while (filepath.back() == '/') {
        filepath.pop_back();
    }

    if (filepath.size() > 0 && filepath.front() != '/') {
        filepath = "/" + filepath;
    }
}

Filepath operator/ (const Filepath& filepath1, const Filepath& filepath2) {
    return filepath1._filepath + filepath2._filepath;
}

std::ostream& operator<< (std::ostream& stream, const Filepath& filepath) {
    return stream << filepath.stringValue();
}
