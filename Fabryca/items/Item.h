#pragma once

#include "Foundation.h"
#include "Object.h"
#include "characters/Character.h"
#include "graphics/Graphics.h"

#include <string>


namespace Game {

class Character;

class Item: public Object {
public:
    enum class Type;
    enum class Rarity;


    Item(const Model& model);
    virtual ~Item() {};


    static Item* create(Type type, Rarity rarity);

    virtual Void applyEffectToCharacter(Character& character) = 0;

private:
    Model _model;
};


enum class Item::Type {
    weapon = 0,
    cure = 1,
    key = 2,
};


enum class Item::Rarity {
    common = 0,
    rare = 1,
    legendary = 2
};

}
