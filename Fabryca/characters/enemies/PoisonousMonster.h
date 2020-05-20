#pragma once

#include "Foundation.h"
#include "characters/enemies/Enemy.h"


namespace Game {

class PoisonousMonster final: public Enemy {
public:
    PoisonousMonster(
        Int maxHealth,
        const Model& model,
        const Configuration& configuration,
        const Point& location,
        Int attackDamage
    );
};

}
