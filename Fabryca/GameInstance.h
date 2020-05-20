#pragma once

#include "Foundation.h"
#include "characters/Player.h"
#include "graphics/Graphics.h"
#include "Configuration.h"
#include "Terrain.h"
#include "utility/Filepath.h"
#include "NumberDisplayer.h"

#include <string>
#include <unordered_map>


namespace Game {

class GameInstance final {
public:
    explicit GameInstance(const Configuration& configuration);
    explicit GameInstance(const Filepath& settingsFilepath);


    const Configuration& configuration() const;
    const Terrain& terrain() const;

    Void processInput();

    Void restart();

private:
    Configuration _configuration;

    Terrain _terrain;
    Player _player;

    Int _score;
    NumberDisplayer _scoreDisplayer;

    Int _healthBonusProbability;
    Int _maxHealthBonus;

    Int _enemyAttackProbability;
    Int _enemyMoveProbability;
    Int _enemyChaseProbability;
    Int _enemyViewDistance;

    Bool _isWaitingForRestart;


    GameInstance(const GameInstance&) = delete;
    GameInstance& operator= (const GameInstance&) = delete;
    GameInstance(GameInstance&&) = delete;
    GameInstance& operator= (GameInstance&&);


    Void _setupScene();

    Void _makePlayerDecisions();
    Void _makeEnemyDecisions();
};

}
