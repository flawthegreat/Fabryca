#pragma once

#include "Foundation.h"
#include "Item.h"

#include <string>


class Weapon: public Item {
public:
    enum class Range;


    Weapon(const Model& model, Range range, Int damage);


    Int damage() const;

    Void applyEffectToCharacter(Character& character) override;

private:
    Range _range;
    Int _damage;
};
