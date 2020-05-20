#pragma once

#include "Foundation.h"
#include "utility/Point.h"
#include "utility/JSON.h"
#include "Configuration.h"
#include "characters/enemies/Enemy.h"

#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>


namespace Game {

struct Cursor {
    Model model;
    Point location;


    Cursor(const Model& model, const Point& location);
};


class Terrain final {
public:
    Terrain(const Configuration& Configuration);

    Terrain(const Terrain&) = delete;
    Terrain& operator= (const Terrain&) = delete;
    Terrain(Terrain&&) = delete;
    Terrain& operator= (Terrain&&) = delete;
    
    ~Terrain();


    const Cursor& cursor() const;
    Point cursorPosition() const;

    Void shiftCursor(Direction direction);
    Void shiftToCursor(const Callback& callback = Callback());

    friend class GameInstance;

private:
    const Configuration& _configuration;

    std::unordered_map<Int, std::unordered_map<Int, Bool>> _blockIsReachable;
    std::unordered_map<Int, std::unordered_map<Int, Model*>> _structures;
    std::unordered_map<Int, std::unordered_map<Int, Enemy*>> _enemies;
    std::unordered_map<Enemy*, Point> _enemyLocation;

    std::vector<Enemy*> _deadEnemies;

    Point _currentLocation;

    Model _wireframe;
    Model _model;
    Cursor _cursor;

    Bool _isMoving;

    Int _viewDistance;
    Double _shiftDuration;
    Int _movingObjects;
    UInt16 _width;
    UInt16 _height;


    Void _alignCamera(Double duration = 0.0) const;

    Void _updateEnemyExistence(Int x, Int y);
    Void _updateEnemyExistence(const Point& location);

    Void _updateEnemyLocation(Enemy* enemy);

    Int _locationPriority(Int y) const;

    Model* _structureAt(Int x, Int y) const;
    Model* _structureAt(const Point& location) const;
    Enemy* _enemyAt(Int x, Int y) const;
    Enemy* _enemyAt(const Point& location) const;
    Model* _modelAt(Int x, Int y) const;
    Model* _modelAt(const Point& location) const;

    Void _makeEnemyDecisions();

    Void _loadStructures();

    Bool _locationIsCorrect(Int x, Int y) const;
    Bool _locationIsCorrect(const Point& location) const;
    Bool _positionIsVisible(Int x, Int y) const;
    Bool _positionIsVisible(const Point& position) const;
};

}
