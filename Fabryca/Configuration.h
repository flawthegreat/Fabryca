#pragma once

#include "utility/JSON.h"
#include "graphics/Graphics.h"
#include "utility/Filepath.h"

#include <string>
#include <unordered_map>


namespace Game {

class Configuration {
public:
    Configuration(const Filepath& settingsFilepath);

    Configuration(const Configuration& configuration);
    Configuration& operator= (const Configuration& configuration);
    Configuration(Configuration&& configuration);
    Configuration& operator= (Configuration&& configuration);
    
    ~Configuration();


    const JSON::Value& settings() const;
    const std::unordered_map<std::string, const Mesh*>& meshes() const;
    const std::unordered_map<std::string, const Texture*>& textures() const;
    const std::unordered_map<std::string, const Shader*>& shaders() const;
    const std::unordered_map<std::string, const Model*>& models() const;
    const std::unordered_map<UInt, std::string>& modelName() const;
    
private:
    JSON::Value _settings;

    std::unordered_map<std::string, const Mesh*> _meshes;
    std::unordered_map<std::string, const Texture*> _textures;
    std::unordered_map<std::string, const Shader*> _shaders;
    std::unordered_map<std::string, const Model*> _models;
    std::unordered_map<UInt, std::string> _modelName;


    Void _delete();

    Void _loadModelData();
    Void _loadModels();
};

}
