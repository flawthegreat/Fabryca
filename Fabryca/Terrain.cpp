#include "Terrain.h"
#include "utility/Random.h"
#include "characters/enemies/Enemy.h"

#include <iostream>

using namespace Game;


Terrain::Terrain(const Point& currentLocation, const Configuration& Configuration):
    _configuration(Configuration),
    _currentLocation(currentLocation),
    _isMoving(false),
    _viewDistance(Configuration.settings()["terrain"]["viewDistance"].asInt()),
    _shiftDuration(Configuration.settings()["terrain"]["shiftDuration"].asDouble()),
    _maxRandomRotationAngle(Configuration.settings()["terrain"]["maxRandomRotationAngle"].asInt())
{
    _loadBlocks();

    Renderer::shared().setHorizontalViewBounds({
        -_viewDistance - 0.5f,
        _viewDistance + 0.5f,
        -_viewDistance - 0.5f,
        _viewDistance + 0.5f
    });

    _wireframe = new Model(*Configuration.models().at("terrainWireframe"));
    _wireframe->setYPosition(0.0005f);
    _wireframe->setScale(1.001f);
    Renderer::shared().addModelToDrawQueue(*_wireframe);

    _frontWall = new Model(*Configuration.models().at("terrainFrontWall"));
    Renderer::shared().addModelToDrawQueue(*_frontWall);

    _cursor = new Structure(Model(*Configuration.models().at("cursor")), { 0, 0 });

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            TerrainBlock* block = &_blocks[currentLocation.x + x][currentLocation.y + y];
            if (!block->model) continue;

            block->model->setXZPosition(x, y);
            block->show();
        }
    }

    _alignCamera();
    _cursor->show();
    shiftToCursor();
}

Terrain::~Terrain() {
    for (auto& blocks: _blocks) {
        for (TerrainBlock& block: blocks) {
            delete block.model;
            delete block.structure;
            delete block.character;
        }
    }

    delete _wireframe;
    delete _frontWall;
    delete _cursor;
}

const Structure& Terrain::cursor() const {
    return *_cursor;
}

Void Terrain::shiftToCursor() {
    const Point direction = -_cursor->location;
    if (direction.x == 0 && direction.y == 0) return;

    if (!_locationIsCorrect(_currentLocation - direction)) return;
    if (_isMoving) return;

    _isMoving = true;
    const Double durationMultiplier = _cursor->location.distanceToOrigin();

    std::vector<Point> blocksToHide;
    std::vector<Point> blocksToShow;
    std::vector<Point> temporaryVisibleBlocks;

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            if (!_positionIsVisible({ x + direction.x, y + direction.y })) {
                blocksToHide.emplace_back(x, y);
            }
            if (!_positionIsVisible({ x - direction.x, y - direction.y })) {
                blocksToShow.emplace_back(x - direction.x, y - direction.y);
            }
            if (!_positionIsVisible({ x - direction.x, y })) {
                temporaryVisibleBlocks.emplace_back(x - direction.x, y);
            }
            if (!_positionIsVisible({ x, y - direction.y })) {
                temporaryVisibleBlocks.emplace_back(x, y - direction.y);
            }
        }
    }

    for (const auto& i: temporaryVisibleBlocks) {
        TerrainBlock* block = &_blocks[_currentLocation.x + i.x][_currentLocation.y + i.y];
        if (!block->model) continue;

        block->model->setXZPosition(i.x, i.y);
        block->model->moveToXZ(
            i.x + direction.x,
            i.y + direction.y,
            _shiftDuration * durationMultiplier,
            [=](Bool) {
                block->hide();
            }
        );
        block->show();
    }

    for (const auto& i: blocksToShow) {
        TerrainBlock* block = &_blocks[_currentLocation.x + i.x][_currentLocation.y + i.y];
        if (!block->model) continue;

        block->model->setXZPosition(i.x, i.y);
        block->show();
    }

    for (const auto& i: blocksToHide) {
        TerrainBlock* block = &_blocks[_currentLocation.x + i.x][_currentLocation.y + i.y];
        if (!block->model) continue;

        block->model->moveToXZ(
            i.x + direction.x,
            i.y + direction.y,
            _shiftDuration * durationMultiplier,
            [=](Bool) {
                block->hide();
            }
        );
    }

    _currentLocation -= direction;

    for (Int x = -_viewDistance; x <= _viewDistance; ++x) {
        for (Int y = -_viewDistance; y <= _viewDistance; ++y) {
            Model* model = _blocks[_currentLocation.x + x][_currentLocation.y + y].model;
            if (!model) continue;

            if (x == 0 && y == 0) {
                model->moveToXZ(x, y, _shiftDuration * durationMultiplier, [&](Bool) {
                    _isMoving = false;
                });
            } else {
                model->moveToXZ(x, y, _shiftDuration * durationMultiplier);
            }
        }
    }

    _cursor->location = { 0, 0 };
    _cursor->model.moveToXZ(0.0f, 0.0f, _shiftDuration * durationMultiplier);
    _alignCamera(_shiftDuration * durationMultiplier);
}

Void Terrain::shiftCursor(Direction direction) {
    if (_isMoving) return;

    Point delta;
    if (direction == Direction::right) {
        delta = { 1, 0 };
    } else if (direction == Direction::up) {
        delta = { 0, -1 };
    } else if (direction == Direction::left) {
        delta = { -1, 0 };
    } else if (direction == Direction::down) {
        delta = { 0, 1 };
    } else {
        throw std::runtime_error("Unknown direction.");
    }

    if (!_positionIsVisible(_cursor->location + delta)) return;

    _cursor->location += delta;

    const auto [x, y] = _currentLocation + _cursor->location;
    const TerrainBlock* block = &_blocks[x][y];
    if (!block->model || block->structure) {
        _cursor->model.texture = *_configuration.textures().at("gray50");
    } else if (block->character) {
        _cursor->model.texture = *_configuration.textures().at("darkRed");
    } else {
        _cursor->model.texture = *_configuration.textures().at("gray0");
    }

    _cursor->model.moveToXZ(_cursor->location.x, _cursor->location.y, _shiftDuration);
    _alignCamera(_shiftDuration);
}

Void Terrain::_alignCamera(Double duration) const {
    Renderer::shared().moveCameraTo(
        _cursor->location.x,
        -static_cast<Double>(_cursor->location.y) / 2.0 + 8,
        Renderer::shared().camera().position().z,
        duration
    );
}

Void Terrain::_loadBlocks() {
    const std::string& dataFilepath = _configuration.settings()["terrain"]["dataPath"].asString();
    FILE* file = fopen((resourcesPath + dataFilepath).c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << dataFilepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read terrain data.");
    }

    fseek(file, 0, SEEK_END);
    const Int size = static_cast<Int>(ftell(file)) - 2;

    std::vector<Byte> data(size);

    rewind(file);
    fread(&_width, 2, 1, file);
    _height = size / _width / 4;

    assert(_locationIsCorrect(_currentLocation));

    fread(&data[0], 1, size, file);
    fclose(file);

    _blocks.resize(_width);

    const Mesh& blockMesh = *_configuration.meshes().at("terrainBlock");
    const Texture& blockTexture = *_configuration.textures().at("gray100");
    const Shader& blockShader = *_configuration.shaders().at("pointLightBounded");

    for (Int x = 0; x < _width; ++x) {
        _blocks[x].reserve(_height);
        for (Int y = 0; y < _height; ++y) {
            const Int i = (y * _width + x) * 4;

            // erhsssss  ssssssss  ttttwwww  pppppppp
            // 00000000  01100100  00000000  11111111
            // e - block is empty
            // r - 1 if object should be randomly rotated
            // h - 1 if enemy should be spawned
            // s - structure ID (0 for no structure)
            // t - enemy type ID (enum value)
            // w - enemy strength (enum value)
            // p - enemy spawn probability (0 - 255)

            const bool isEmpty = (data[i] >> 7) & 1;
            if (isEmpty) {
                _blocks[x].emplace_back(nullptr);

                continue;
            }

            const Bool randomRotation = (data[i] >> 6) & 1;
            const UInt16 structure = ((data[i] & 0b00011111) << 8) + data[i + 1];
            const Bool spawnEnemy = (data[i] & 0b00100000) >> 5;
            const Int enemyType = ((data[i + 2] & 0b11110000) >> 4);
            const Byte enemyStrength = data[i + 2] & 0b00000111;
            const Byte enemySpawnProbability = data[i + 3];
//            const Bool enemyIsDead = false;

            _blocks[x].emplace_back(new Model(blockMesh, blockTexture, blockShader));

            if (spawnEnemy && Random::valueInRange(1, ByteMax) <= enemySpawnProbability) {
                _blocks[x][y].assignCharacter(Enemy::create(
                    _configuration,
                    static_cast<Enemy::Type>(enemyType),
                    static_cast<Enemy::Strength>(enemyStrength),
                    { x, y }
                ));

                if (!randomRotation) continue;

                _blocks[x][y].character->model().setYRotation(
                    Random::valueInRange(-_maxRandomRotationAngle, _maxRandomRotationAngle)
                );

                continue;
            }

            if (!structure) continue;

            _blocks[x][y].assignStructure(
                new Structure(*_configuration.models().at(_configuration.modelName().at(structure)),
                { x, y })
            );

            if (!randomRotation) continue;

            _blocks[x][y].structure->model.setYRotation(
                Random::valueInRange(-_maxRandomRotationAngle, _maxRandomRotationAngle)
            );
        }
    }
}

Bool Terrain::_locationIsCorrect(const Point& location) {
    return location.x - _viewDistance >= 0 &&
        location.y - _viewDistance >= 0 &&
        location.x + _viewDistance < _width &&
        location.y + _viewDistance < _height;
}

Bool Terrain::_positionIsVisible(const Point& position) {
    return position.x >= -_viewDistance &&
        position.y >= -_viewDistance &&
        position.x <= _viewDistance &&
        position.y <= _viewDistance;
}
