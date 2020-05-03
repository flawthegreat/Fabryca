#pragma once

#include "Foundation.h"
#include "Item.h"


namespace Game {

class KeyItem final: public Item {
public:
    KeyItem(const Model& model);


    Void applyEffectToCharacter(Character& character) override;
};

}
