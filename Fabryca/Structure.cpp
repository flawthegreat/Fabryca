#include "Structure.h"

using namespace Game;


Structure::Structure(const Model& model, const Point& location):
    model(model),
    location(location)
{}

Void Structure::show() const {
    Renderer::shared().addModelToDrawQueue(
        model,
        model.texture.isOpaque() ? 1 : IntMax - location.y
    );
}

Void Structure::hide() const {
    Renderer::shared().removeModelFromDrawQueue(model);
}
