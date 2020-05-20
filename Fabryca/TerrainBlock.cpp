#include "TerrainBlock.h"

using namespace Game;


TerrainBlock::TerrainBlock(Model* model):
    model(model),
    structure(nullptr),
    character(nullptr)
{}

Bool TerrainBlock::isOccupied() const {
    return structure != nullptr || character != nullptr;
}

Void TerrainBlock::assignStructure(Structure* structure) {
    this->structure = structure;

    if (structure) {
        model->addChild(&structure->model);
    }
}

Void TerrainBlock::assignCharacter(Character* character) {
    this->character = character;

    if (character) {
        model->addChild(&character->model());
    }
}

Character* TerrainBlock::unassignCharacter() {
    if (!character) return nullptr;

    model->removeChild(&character->model());

    return character;
}

Void TerrainBlock::show() const {
    Renderer::shared().addModelToDrawQueue(*model);
    if (structure) {
        structure->show();
    }
    if (character) {
        character->spawn();
    }
}

Void TerrainBlock::hide() const {
    Renderer::shared().removeModelFromDrawQueue(*model);
    if (structure) {
        structure->hide();
    }
    if (character) {
        character->despawn();
    }
}
