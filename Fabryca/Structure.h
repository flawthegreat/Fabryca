#pragma once

#include "Foundation.h"
#include "Object.h"
#include "graphics/Graphics.h"
#include "utility/Point.h"


namespace Game {

struct Structure final: public Object {
    Model model;
    Point location;


    Structure(const Model& model, const Point& location);


    Void show() const;
    Void hide() const;
};

}
