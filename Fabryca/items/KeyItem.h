#pragma once

#include "Foundation.h"
#include "Item.h"


class Key: public Item {
public:
    Key();


    Void applyEffectToCharacter(Character& character) override;
};
