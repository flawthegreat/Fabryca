#pragma once

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class HoveringBeast final: public Enemy {
public:
    HoveringBeast(const std::string& name, Int maxHealth, const NumericAttribute& attackDamage);

    
    Void attackCharacter(Character& character) const override;
};
