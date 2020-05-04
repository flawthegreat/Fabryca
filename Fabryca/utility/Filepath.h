#pragma once

#include "Foundation.h"

#include <string>
#include <iostream>


class Filepath {
public:
    Filepath(const std::string& filepath);
    Filepath& operator= (const std::string& filepath);
    Filepath(const Char* filepath);
    Filepath& operator= (const Char* filepath);


    std::string stringValue() const;

    operator std::string () const;

    Filepath& operator+= (const Filepath& filepath);

    static const std::string& rootFilepath();
    static Void setRootFilepath(const std::string& newPath);

    friend Filepath operator/ (const Filepath&, const Filepath&);

private:
    std::string _filepath;

    static std::string _rootFilepath;


    static Void _fixFormat(std::string& filepath);
};

Filepath operator/ (const Filepath& filepath1, const Filepath& filepath2);
std::ostream& operator<< (std::ostream& stream, const Filepath& filepath);
