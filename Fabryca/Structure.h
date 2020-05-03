#pragma once

#include "Foundation.h"
#include "GameObject.h"
#include "graphics/Graphics.h"
#include "utility/Point.h"


struct Structure final: public GameObject {
    Model* model;
    Point location;


    Structure(Model* model, const Point& location);
};
