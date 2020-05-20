#pragma once

#include "Foundation.h"
#include "items/Item.h"

#include <string>


namespace Game {

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

}
