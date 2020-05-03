#pragma once

#include "Foundation.h"
#include "utility/Point.h"
#include "utility/JSON.h"
#include "Configuration.h"
#include "TerrainBlock.h"
#include "Structure.h"

#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>


namespace Game {

class Terrain final {
public:
    Terrain(const Point& currentLocation, const Configuration& Configuration);
    Terrain(const Terrain&) = delete;
    Terrain& operator= (const Terrain&) = delete;
    Terrain(Terrain&&) = delete;
    Terrain& operator= (Terrain&&) = delete;
    ~Terrain();


    const Structure& cursor() const;

    Void shiftToCursor();
    Void shiftCursor(Direction direction);

private:
    const Configuration& _configuration;

    std::vector<std::vector<TerrainBlock>> _blocks;

    Model* _wireframe;
    Model* _frontWall;
    Structure* _cursor;

    Point _currentLocation;
    Bool _isMoving;

    UInt16 _width;
    UInt16 _height;

    const Int _viewDistance;
    const Double _shiftDuration;
    const Int _maxRandomRotationAngle;


    Void _alignCamera(Double duration = 0.0) const;

    Void _loadBlocks();

    Bool _locationIsCorrect(const Point& location);
    Bool _positionIsVisible(const Point& position);
};

}
