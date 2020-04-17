#pragma once

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class ForestDemon final: public Enemy {
public:
    ForestDemon(const std::string& name, Int maxHealth,  const NumericAttribute& attackDamage);


    Void attackCharacter(Character& character) const override;
};
