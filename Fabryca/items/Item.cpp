#include "Item.h"

#include <stdexcept>

using namespace Game;


Item::Item(const Model& model):
    _model(model)
{}

Item* Item::create(Type type, Rarity rarity) {
//    static_assert(false, "TODO");
    return nullptr;
};
