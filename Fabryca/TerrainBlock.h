#pragma once

#include "Foundation.h"
#include "graphics/Graphics.h"
#include "Structure.h"
#include "characters/Character.h"


namespace Game {

struct TerrainBlock final {
    Model* model;
    Structure* structure;
    Character* character;


    TerrainBlock(Model* model);


    Bool isOccupied() const;

    Void assignStructure(Structure* structure);

    Void assignCharacter(Character* character);
    Character* unassignCharacter();

    Void show() const;
    Void hide() const;
};

}
