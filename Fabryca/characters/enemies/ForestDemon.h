#pragma once

#include "Foundation.h"
#include "characters/enemies/Enemy.h"


namespace Game {

class ForestDemon final: public Enemy {
public:
    ForestDemon(
        Int maxHealth,
        const Model& model,
        Double movementSpeed,
        const Point& location,
        Int attackDamage
    );


    Void attackCharacter(Character& character) const override;
};

}
