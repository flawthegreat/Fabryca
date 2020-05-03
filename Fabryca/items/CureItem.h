#pragma once

#include "Foundation.h"
#include "Item.h"


class Cure: public Item {
public:
    Cure(Int amount);


    Int amount() const;

    Void applyEffectToCharacter(Character& character) override;

private:
    Int _amount;
};
