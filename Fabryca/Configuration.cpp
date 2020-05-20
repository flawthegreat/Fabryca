#include "Configuration.h"

using namespace Game;


Configuration::Configuration(const Filepath& settingsFilepath) {
    JSON::read(settingsFilepath, _settings);
    _loadModelData();
    _loadModels();
}

Configuration::Configuration(const Configuration& configuration):
    _settings(configuration._settings)
{
    for (const auto& [key, value]: configuration._meshes) {
        _meshes.emplace(key, new Mesh(*value));
    }
    for (const auto& [key, value]: configuration._textures) {
        _textures.emplace(key, new Texture(*value));
    }
    for (const auto& [key, value]: configuration._shaders) {
        _shaders.emplace(key, new Shader(*value));
    }
    for (const auto& [key, value]: configuration._models) {
        _models.emplace(key, new Model(*value));
    }
    for (const auto& [key, value]: configuration._modelName) {
        _modelName.emplace(key, value);
    }
}

Configuration& Configuration::operator= (const Configuration& configuration) {
    if (this == &configuration) return *this;

    _delete();

    _settings = configuration._settings;

    for (const auto& [key, value]: configuration._meshes) {
        _meshes.emplace(key, new Mesh(*value));
    }
    for (const auto& [key, value]: configuration._textures) {
        _textures.emplace(key, new Texture(*value));
    }
    for (const auto& [key, value]: configuration._shaders) {
        _shaders.emplace(key, new Shader(*value));
    }
    for (const auto& [key, value]: configuration._models) {
        _models.emplace(key, new Model(*value));
    }
    for (const auto& [key, value]: configuration._modelName) {
        _modelName.emplace(key, value);
    }

    return *this;
}

Configuration::Configuration(Configuration&& configuration):
    _settings(std::move(configuration._settings))
{
    for (auto& [key, value]: configuration._meshes) {
        _meshes.emplace(std::move(key), value);
        value = nullptr;
    }
    for (auto& [key, value]: configuration._textures) {
        _textures.emplace(std::move(key), value);
        value = nullptr;
    }
    for (auto& [key, value]: configuration._shaders) {
        _shaders.emplace(std::move(key), value);
        value = nullptr;
    }
    for (auto& [key, value]: configuration._models) {
        _models.emplace(std::move(key), value);
        value = nullptr;
    }
    for (auto& [key, value]: configuration._modelName) {
        _modelName.emplace(std::move(key), value);
        value = nullptr;
    }
}

Configuration& Configuration::operator= (Configuration&& configuration) {
    if (this == &configuration) return *this;

    _delete();

    _settings = std::move(configuration._settings);
    configuration._settings = JSON::Value();

    for (auto& [key, value]: configuration._meshes) {
        _meshes.emplace(std::move(key), std::move(value));
        value = nullptr;
    }
    for (auto& [key, value]: configuration._textures) {
        _textures.emplace(std::move(key), std::move(value));
        value = nullptr;
    }
    for (auto& [key, value]: configuration._shaders) {
        _shaders.emplace(std::move(key), std::move(value));
        value = nullptr;
    }
    for (auto& [key, value]: configuration._models) {
        _models.emplace(std::move(key), std::move(value));
        value = nullptr;
    }
    for (auto& [key, value]: configuration._modelName) {
        _modelName.emplace(std::move(key), std::move(value));
        value = nullptr;
    }

    return *this;
}

Configuration::~Configuration() {
    _delete();
}

Void Configuration::_delete() {
    for (const auto& model: _models) { delete model.second; }
    for (const auto& mesh: _meshes) { delete mesh.second; }
    for (const auto& texture: _textures) { delete texture.second; }
    for (const auto& shader: _shaders) { delete shader.second; }
}

const JSON::Value& Configuration::settings() const {
    return _settings;
}

const std::unordered_map<std::string, const Mesh*>& Configuration::meshes() const {
    return _meshes;
}

const std::unordered_map<std::string, const Texture*>& Configuration::textures() const {
    return _textures;
}

const std::unordered_map<std::string, const Shader*>& Configuration::shaders() const {
    return _shaders;
}

const std::unordered_map<std::string, const Model*>& Configuration::models() const {
    return _models;
}

const std::unordered_map<UInt, std::string>& Configuration::modelName() const {
    return _modelName;
}

Void Configuration::_loadModelData() {
    const JSON::Value* paths = &_settings["modelData"]["meshes"];
    for (auto itr = paths->begin(); itr != paths->end(); ++itr) {
        const std::string& key = itr.key().asString();
        _meshes.emplace(key, new Mesh((*paths)[key].asString()));
    }

    paths = &_settings["modelData"]["textures"];
    for (auto itr = paths->begin(); itr != paths->end(); ++itr) {
        const std::string& key = itr.key().asString();
        _textures.emplace(key, new Texture((*paths)[key].asString()));
    }

    paths = &_settings["modelData"]["shaders"];
    for (auto itr = paths->begin(); itr != paths->end(); ++itr) {
        const std::string& key = itr.key().asString();
        _shaders.emplace(key, new Shader((*paths)[key].asString()));
    }
}

Void Configuration::_loadModels() {
    const JSON::Value& modelData = _settings["models"];
    for (auto itr = modelData.begin(); itr != modelData.end(); ++itr) {
        const std::string& key = itr.key().asString();
        _modelName[modelData[key]["id"].asInt()] = key;
        _models.emplace(key, new Model(
            *_meshes[modelData[key]["mesh"].asString()],
            *_textures[modelData[key]["texture"].asString()],
            *_shaders[modelData[key]["shader"].asString()]
        ));
    }
}
