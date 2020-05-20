#include "Terrain.h"
#include "utility/Random.h"
#include "characters/enemies/Enemy.h"

#include <iostream>

using namespace Game;

template class EventManager<Character>;


Cursor::Cursor(const Model& model, const Point& location):
    model(model),
    location(location)
{}


Terrain::Terrain(const Configuration& configuration):
    _configuration(configuration),
    _currentLocation({
        _configuration.settings()["constants"]["startLocation"][0].asInt(),
        _configuration.settings()["constants"]["startLocation"][1].asInt()
    }),
    _wireframe(*_configuration.models().at("terrainWireframe")),
    _model(*_configuration.models().at("terrain")),
    _cursor(*_configuration.models().at("cursor"), _currentLocation),
    _isMoving(false),
    _viewDistance(_configuration.settings()["terrain"]["viewDistance"].asInt()),
    _shiftDuration(_configuration.settings()["terrain"]["shiftDuration"].asDouble()),
    _movingObjects(0)
{
    _loadStructures();

    Renderer::shared().setHorizontalViewBounds({
        -_viewDistance - 0.5f,
        _viewDistance + 0.5f,
        -_viewDistance - 0.5f,
        _viewDistance + 0.5f
    });

    _wireframe.setYPosition(0.0005f);
    _wireframe.setScale(1.001f);

    _wireframe.show();
    _model.show();
    _cursor.model.show();

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            Model* structure = _structureAt(_currentLocation.x + x, _currentLocation.y + y);
            if (structure) {
                structure->setXZPosition(x, y);
                structure->show(_locationPriority(_currentLocation.y + y));
            }

            Enemy* enemy = _enemyAt(_currentLocation.x + x, _currentLocation.y + y);
            if (!enemy) continue;

            enemy->model().setXZPosition(x, y);
            enemy->spawn();
        }
    }
}

Terrain::~Terrain() {
    for (auto& [_, structures]: _structures) {
        for (auto [_, structure]: structures) { delete structure; }
    }

    for (auto& [_, enemies]: _enemies) {
        for (auto [_, enemy]: enemies) { delete enemy; }
    }

    for (auto enemy: _deadEnemies) { delete enemy; }
}

const Cursor& Terrain::cursor() const {
    return _cursor;
}

Point Terrain::cursorPosition() const {
    return _cursor.location - _currentLocation;
}

Void Terrain::shiftCursor(Direction direction) {
    if (_isMoving) return;

    Point offset;
    if (direction == Direction::right) offset = { 1, 0 };
    else if (direction == Direction::up) offset = { 0, -1 };
    else if (direction == Direction::left) offset = { -1, 0 };
    else if (direction == Direction::down) offset = { 0, 1 };
    else throw std::runtime_error("Unknown direction.");

    const Point position = cursorPosition();

    if (!_positionIsVisible(position + offset)) return;

    _cursor.location += offset;
    const auto [x, y] = _cursor.location;
    if (!_blockIsReachable[x][y] || abs(position.x + offset.x) + abs(position.y + offset.y) > 1) {
        _cursor.model.texture = *_configuration.textures().at("gray50");
    } else if (_enemyAt(_cursor.location)) {
        _cursor.model.texture = *_configuration.textures().at("darkRed");
    } else {
        _cursor.model.texture = *_configuration.textures().at("gray0");
    }

    _cursor.model.moveToXZ(position.x + offset.x, position.y + offset.y, _shiftDuration);
    _alignCamera(_shiftDuration);
}

Void Terrain::shiftToCursor(const Callback& callback) {
    if (_movingObjects > 0) {
        if (callback) { callback(false); }

        return;
    }

    const Point direction = -cursorPosition();
    if (abs(direction.x) + abs(direction.y) > 1 || direction == Point()) return;

    if (!_locationIsCorrect(_currentLocation - direction) || _isMoving) {
        if (callback) { callback(false); }

        return;
    }

    _isMoving = true;
    const Double shiftDuration = direction.distanceToOrigin() * _shiftDuration;

    std::vector<std::pair<Model*, Point>> structuresToHide;
    std::vector<std::pair<Model*, Point>> structuresToShow;

    std::vector<std::pair<Enemy*, Point>> enemiesToHide;
    std::vector<std::pair<Enemy*, Point>> enemiesToShow;

    Model* structure = nullptr;
    Enemy* enemy = nullptr;
    Point positiveOffset;
    Point negativeOffset;

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            const Point position(x, y);
            positiveOffset = position + direction;
            negativeOffset = position - direction;

            if (!_positionIsVisible(positiveOffset)) {
                if ((structure = _structureAt(_currentLocation + position))) {
                    structuresToHide.emplace_back(structure, position);
                }
                if ((enemy = _enemyAt(_currentLocation + position))) {
                    enemiesToHide.emplace_back(enemy, position);
                }
            }
            if (!_positionIsVisible(negativeOffset)) {
                if ((structure = _structureAt(_currentLocation + negativeOffset))) {
                    structuresToShow.emplace_back(structure, negativeOffset);
                }
                if ((enemy = _enemyAt(_currentLocation + negativeOffset))) {
                    enemiesToShow.emplace_back(enemy, negativeOffset);
                }
            }
        }
    }

    for (const auto& [model, position]: structuresToShow) {
        model->setXZPosition(position.x, position.y);
        model->show(_locationPriority(_currentLocation.y + position.y));
    }

    for (const auto& [enemy, position]: enemiesToShow) {
        enemy->model().setXZPosition(position.x, position.y);
        enemy->spawn();
    }

    for (const auto& [model, position]: structuresToHide) {
        ++_movingObjects;
        model->moveToXZ(
            position.x + direction.x,
            position.y + direction.y,
            shiftDuration,
            [=, model=model](Bool) {
                model->hide();
                --this->_movingObjects;
            }
        );
    }

    for (const auto& [enemy, position]: enemiesToHide) {
        ++_movingObjects;
        enemy->model().moveToXZ(
            position.x + direction.x,
            position.y + direction.y,
            shiftDuration,
            [=, enemy=enemy](Bool) {
                enemy->despawn();
                --this->_movingObjects;
            }
        );
    }

    _currentLocation -= direction;

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            if ((structure = _structureAt(_currentLocation.x + x, _currentLocation.y + y))) {
                ++_movingObjects;
                structure->moveToXZ(x, y, shiftDuration, [&](Bool) { --_movingObjects; });
            }
            if ((enemy = _enemyAt(_currentLocation.x + x, _currentLocation.y + y))) {
                ++_movingObjects;
                enemy->model().moveToXZ(x, y, shiftDuration, [&](Bool) { --_movingObjects; });
            }
        }
    }

    _wireframe.moveTo(_wireframe.position(), shiftDuration, [&, callback](Bool) {
        _isMoving = false;

        if (callback) { callback(true); }
    });

    _cursor.model.texture = *_configuration.textures().at("gray0");
    _cursor.location = _currentLocation;
    _cursor.model.moveToXZ(0.0f, 0.0f, shiftDuration);

    _alignCamera(shiftDuration);
}

Void Terrain::_alignCamera(Double duration) const {
    const auto [x, y] = cursorPosition();
    Renderer::shared().moveCameraTo(
        x,
        -static_cast<Double>(y) / 2.0 + 8,
        Renderer::shared().camera().position().z,
        duration
    );
}

Void Terrain::_enemyHasDied(Enemy* enemy) {
    _enemies[enemy->location().x][enemy->location().y] = nullptr;
    _deadEnemies.emplace_back(enemy);
}

Void Terrain::_updateEnemyLocation(Enemy* enemy) {
    const Point oldLocation = _enemyLocation[enemy];
    const Point newLocation = _enemyLocation[enemy] = enemy->location();
    _enemies[oldLocation.x][oldLocation.y] = nullptr;
    _enemies[newLocation.x][newLocation.y] = enemy;
}

Int Terrain::_locationPriority(Int y) const {
    return IntMax / 2 - y;
}

Void Terrain::_loadStructures() {
    const Filepath& dataFilepath = _configuration.settings()["terrain"]["dataPath"].asString();
    FILE* file = fopen(dataFilepath.stringValue().c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << dataFilepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read terrain data.");
    }

    fseek(file, 0, SEEK_END);
    const Int size = static_cast<Int>(ftell(file)) - 2;

    std::vector<Byte> data(size);

    rewind(file);
    fread(&_width, 2, 1, file);
    _height = size / _width / 3;

    fread(&data[0], 1, size, file);
    fclose(file);

    const Int maxRotation = _configuration.settings()["terrain"]["maxRandomRotationAngle"].asInt();

    for (Int x = 0; x < _width; ++x) {
        for (Int y = 0; y < _height; ++y) {
            const Int i = (y * _width + x) * 3;

            // ssssssss  rRttttSS  ppppppp
            // s - structure ID (0 for no structure)
            // r - 1 if block is reachable
            // R - 1 if object should be randomly rotated
            // t - enemy type ID (enum value)
            // S - enemy strength (enum value)
            // p - enemy spawn probability (0 - 255)

            const Byte structure = data[i];
            const Bool isReachable = (data[i + 1] >> 7) & 1;
            const Bool randomRotation = (data[i + 1] >> 6) & 1;
            const Byte enemyType = (data[i + 1] >> 2) & 0b1111;
            const Byte enemyStrength = data[i + 1] & 0b11;
            const Byte enemySpawnProbability = data[i + 2];

            _blockIsReachable[x][y] = isReachable;

            if (Random::valueInRange(1, ByteMax) <= enemySpawnProbability) {
                Enemy* enemy = Enemy::create(
                    _configuration,
                    static_cast<Enemy::Type>(enemyType),
                    static_cast<Enemy::Strength>(enemyStrength),
                    { x, y }
                );
                _enemies[x][y] = enemy;
                _enemyLocation[enemy] = { x, y };
                enemy->addEventListener("move", [&](Character* enemy) {
                    _updateEnemyLocation(dynamic_cast<Enemy*>(enemy));
                });
                enemy->addEventListener("die", [&](Character* enemy) {
                    _enemyHasDied(dynamic_cast<Enemy*>(enemy));
                });

                if (!randomRotation) continue;

                _enemies[x][y]->model().setYRotation(
                    Random::valueInRange(-maxRotation, maxRotation)
                );

                continue;
            }

            if (!structure) continue;

            _structures[x][y] = new Model(
                *_configuration.models().at(_configuration.modelName().at(structure))
            );

            if (!randomRotation) continue;

            _structures[x][y]->setYRotation(Random::valueInRange(-maxRotation, maxRotation));
        }
    }
}

Model* Terrain::_structureAt(Int x, Int y) const {
    auto xIterator = _structures.find(x);
    if (xIterator == _structures.end()) return nullptr;

    auto yIterator = xIterator->second.find(y);
    if (yIterator == xIterator->second.end()) return nullptr;

    return yIterator->second;
}

Model* Terrain::_structureAt(const Point& location) const {
    return _structureAt(location.x, location.y);
}

Enemy* Terrain::_enemyAt(Int x, Int y) const {
    auto xIterator = _enemies.find(x);
    if (xIterator == _enemies.end()) return nullptr;

    auto yIterator = xIterator->second.find(y);
    if (yIterator == xIterator->second.end()) return nullptr;

    return yIterator->second;
}

Enemy* Terrain::_enemyAt(const Point& location) const {
    return _enemyAt(location.x, location.y);
}

Model* Terrain::_modelAt(Int x, Int y) const {
    Model* structure = _structureAt(x, y);
    if (structure) return structure;

    Enemy* enemy = _enemyAt(x, y);
    if (enemy) return &enemy->model();

    return nullptr;
}

Model* Terrain::_modelAt(const Point& location) const {
    return _modelAt(location.x, location.y);
}

Bool Terrain::_locationIsCorrect(Int x, Int y) const {
    return x - _viewDistance >= 0 &&
        y - _viewDistance >= 0 &&
        x + _viewDistance < _width &&
        y + _viewDistance < _height;
}

Bool Terrain::_locationIsCorrect(const Point& location) const {
    return _locationIsCorrect(location.x, location.y);
}

Bool Terrain::_positionIsVisible(Int x, Int y) const {
    return x >= -_viewDistance &&
        y >= -_viewDistance &&
        x <= _viewDistance &&
        y <= _viewDistance;
}

Bool Terrain::_positionIsVisible(const Point& position) const {
    return _positionIsVisible(position.x, position.y);
}
