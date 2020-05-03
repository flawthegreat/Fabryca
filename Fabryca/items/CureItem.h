#pragma once

#include "Foundation.h"
#include "Item.h"


namespace Game {

class CureItem final: public Item {
public:
    CureItem(const Model& model, Int healthAmount);


    Int healthAmount() const;

    Void applyEffectToCharacter(Character& character) override;

private:
    Int _healthAmount;
};

}
