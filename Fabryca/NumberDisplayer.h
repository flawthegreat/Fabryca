#pragma once

#include "Foundation.h"
#include "graphics/Graphics.h"
#include "Configuration.h"

#include <vector>


namespace Game {

class NumberDisplayer {
public:
    NumberDisplayer(Int value, Byte fieldLength, const Configuration& configuration);


    const Model& anchor() const;
    Model& anchor();

    Void setValue(Int value);

    Void show() const;
    Void hide() const;

private:
    Model _anchor;

    std::vector<Mesh> _digitMeshes;
    std::vector<Model> _displayedValue;
};

};
