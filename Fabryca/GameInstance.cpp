#include "GameInstance.h"
#include "utility/Random.h"

#include <stdexcept>

using namespace Game;


GameInstance::GameInstance(const Configuration& configuration):
    _configuration(configuration),
    _terrain(_configuration),
    _player(_configuration),
    _score(0),
    _scoreDisplayer(0, 2, _configuration),
    _healthBonusProbability(
        _configuration.settings()["constants"]["healthBonusProbability"].asInt()
    ),
    _maxHealthBonus(_configuration.settings()["constants"]["maxHealthBonus"].asInt()),
    _enemyAttackProbability(
        _configuration.settings()["constants"]["enemyAttackProbability"].asInt()
    ),
    _enemyMoveProbability(_configuration.settings()["constants"]["enemyMoveProbability"].asInt()),
    _enemyChaseProbability(_configuration.settings()["constants"]["enemyChaseProbability"].asInt()),
    _enemyViewDistance(_configuration.settings()["constants"]["enemyViewDistance"].asInt()),
    _isWaitingForRestart(false)
{
    Renderer& renderer = Renderer::shared();

    renderer.setClearColor(glm::vec4(1.0f));
    renderer.setCameraPosition(
        _configuration.settings()["constants"]["cameraPosition"][0].asInt(),
        _configuration.settings()["constants"]["cameraPosition"][1].asInt(),
        _configuration.settings()["constants"]["cameraPosition"][2].asInt()
    );

    renderer.setLightPosition(
        _configuration.settings()["constants"]["lightPosition"][0].asInt(),
        _configuration.settings()["constants"]["lightPosition"][1].asInt(),
        _configuration.settings()["constants"]["lightPosition"][2].asInt()
    );
    renderer.setLightDirection(
        _configuration.settings()["constants"]["lightDirection"][0].asInt(),
        _configuration.settings()["constants"]["lightDirection"][1].asInt(),
        _configuration.settings()["constants"]["lightDirection"][2].asInt()
    );
    renderer.setLightPower(
        _configuration.settings()["constants"]["lightPower"].asFloat()
    );

    renderer.setViewDistance(
        _configuration.settings()["constants"]["viewDistance"].asInt()
    );

    renderer.setCameraPosition(0, 8, 11);

    _player.spawn();
    _player.addEventListener("die", [&](Character* player) {
        _isWaitingForRestart = true;
    });

    _scoreDisplayer.anchor().setXYPosition(-5.0f / 32.0f, 3.5f);
    _scoreDisplayer.show();
}

GameInstance::GameInstance(const Filepath& settingsFilepath):
    GameInstance(Configuration(settingsFilepath))
{}

Void GameInstance::restart() {
    Renderer::shared().clearAnimationQueue();
    Renderer::shared().clearDrawQueue();
    Configuration configuration = _configuration;
    this->~GameInstance();
    new(this) GameInstance(configuration);
}

const Configuration& GameInstance::configuration() const {
    return _configuration;
}

const Terrain& GameInstance::terrain() const {
    return _terrain;
}

Void GameInstance::processInput() {
    if (
        WindowManager::shared().keyWasPressed(Key::d) ||
        WindowManager::shared().keyWasPressed(Key::l) ||
        WindowManager::shared().keyWasPressed(Key::right)
    ) {
        _terrain.shiftCursor(Direction::right);
    }
    if (
        WindowManager::shared().keyWasPressed(Key::a) ||
        WindowManager::shared().keyWasPressed(Key::j) ||
        WindowManager::shared().keyWasPressed(Key::left)
    ) {
        _terrain.shiftCursor(Direction::left);
    }
    if (
        WindowManager::shared().keyWasPressed(Key::w) ||
        WindowManager::shared().keyWasPressed(Key::i) ||
        WindowManager::shared().keyWasPressed(Key::up)
    ) {
        _terrain.shiftCursor(Direction::up);
    }
    if (
        WindowManager::shared().keyWasPressed(Key::s) ||
        WindowManager::shared().keyWasPressed(Key::k) ||
        WindowManager::shared().keyWasPressed(Key::down)
    ) {
        _terrain.shiftCursor(Direction::down);
    }

    if (
        WindowManager::shared().keyWasPressed(Key::enter) ||
        WindowManager::shared().keyWasPressed(Key::space)
    ) {
        if (!_isWaitingForRestart) {
            _makePlayerDecisions();
        } else {
            restart();
        }
    }
}

Void GameInstance::_makePlayerDecisions() {
    const Point cursorPosition = _terrain.cursorPosition();
    if (
        _terrain._movingObjects > 0 ||
        _terrain._isMoving ||
        abs(cursorPosition.x) + abs(cursorPosition.y) > 1
    ) return;

    if (cursorPosition.x == 0 && cursorPosition.y == 0) {
        _makeEnemyDecisions();

        return;
    }

    if (!_terrain._blockIsReachable[_terrain._cursor.location.x][_terrain._cursor.location.y]) {
        return;
    }

    Enemy* enemy = _terrain._enemyAt(_terrain._cursor.location);
    if (enemy) {
        _player.attackCharacter(*enemy);
        if (enemy->health() == 0) {
            _terrain._cursor.model.texture = *_configuration.textures().at("gray0");
            _scoreDisplayer.setValue(++_score);

            if (Random::valueInRange(1, 100) <= _healthBonusProbability) {
                _player.increaseHealthBy(Random::valueInRange(1, _maxHealthBonus));
            }
        }

        _makeEnemyDecisions();

        return;
    }

    _terrain.shiftToCursor([game=this](Bool) { game->_makeEnemyDecisions(); });
}

Void GameInstance::_makeEnemyDecisions() {
    std::vector<Enemy*> visibleEnemies;
    for (Int x = -_terrain._viewDistance; x <= _terrain._viewDistance; ++x) {
        for (Int y = -_terrain._viewDistance; y <= _terrain._viewDistance; ++y) {
            Enemy* enemy = _terrain._enemyAt(_terrain._currentLocation + Point(x, y));
            if (!enemy) continue;

            visibleEnemies.emplace_back(enemy);
        }
    }

    for (Enemy* enemy: visibleEnemies) {
        const Point oldLocation = enemy->location();
        const Point position = oldLocation - _terrain._currentLocation;

        if (
            position.distanceToOrigin() > _enemyViewDistance ||
            (position.x == 0 && position.y > 1)
        ) {
            if (Random::valueInRange(1, 100) > _enemyMoveProbability) continue;

            Point offset(Random::valueInRange(-1, 1), 0);
            if (!offset.x) {
                offset.y = Random::valueInRange(-static_cast<Int>(position.y > 1), 1);
            }
            const Point newLocation = oldLocation + offset;

            if (
                !_terrain._positionIsVisible(position + offset) ||
                !_terrain._blockIsReachable[newLocation.x][newLocation.y] ||
                _terrain._enemyAt(newLocation)
            ) continue;

            ++_terrain._movingObjects;
            enemy->moveTo(newLocation, [&](Bool) {
                --_terrain._movingObjects;
            });

            continue;
        }

        if (
            _terrain._currentLocation == _terrain._cursor.location &&
            _terrain._structureAt(_terrain._currentLocation)
        ) continue;

        if (abs(position.x) + abs(position.y) == 1 && !(position.x == 0 && position.y == 1)) {
            if (Random::valueInRange(1, 100) > _enemyAttackProbability) continue;

            enemy->attackCharacter(_player);

            continue;
        } else if (abs(position.x) + abs(position.y) == 1) {
            if (Random::valueInRange(1, 100) > _enemyAttackProbability / 3) continue;

            enemy->attackCharacter(_player);

            continue;
        }

        if (Random::valueInRange(1, 100) > _enemyChaseProbability) continue;

        auto normalize = [&](Int number) { return number > 0 ? 1 : (number < 0 ? -1 : 0); };
        Point playerDirection = { -normalize(position.x), -normalize(position.y) };

        Bool canMoveX = playerDirection.x && _terrain._blockIsReachable[
            enemy->location().x + playerDirection.x
        ][
            enemy->location().y
        ] && !_terrain._enemyAt(enemy->location().x + playerDirection.x, enemy->location().y);
        if (abs(position.x) == 1 && position.y > 0) {
            canMoveX = false;
        }

        const Bool canMoveY = playerDirection.y && _terrain._blockIsReachable[enemy->location().x][
            enemy->location().y + playerDirection.y
        ] && !_terrain._enemyAt(enemy->location().x, enemy->location().y + playerDirection.y);

        if (!canMoveX && !canMoveY) continue;

        if (canMoveX && canMoveY) {
            if (Random::valueInRange(0, 1)) {
                playerDirection.x = 0;
            } else {
                playerDirection.y = 0;
            }
        } else if (canMoveX) {
            playerDirection.y = 0;
        } else {
            playerDirection.x = 0;
        }

        const Point newLocation = oldLocation + playerDirection;
        ++_terrain._movingObjects;
        enemy->moveTo(newLocation, [&, enemy, newLocation](Bool) {
            --_terrain._movingObjects;

            const Point newPosition = newLocation - _terrain._currentLocation;
            if (
                abs(newPosition.x) + abs(newPosition.y) == 1 &&
                Random::valueInRange(1, 100) <= _enemyAttackProbability
            ) {
                enemy->attackCharacter(_player);
            }
        });
    }
}
