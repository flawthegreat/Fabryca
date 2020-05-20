#pragma once

#include "Foundation.h"
#include "characters/enemies/Enemy.h"


namespace Game {

class HoveringBeast final: public Enemy {
public:
    HoveringBeast(
        Int maxHealth,
        const Model& model,
        Double movementSpeed,
        const Point& location,
        Int attackDamage
    );

    
    Void attackCharacter(Character& character) const override;
};

}
