#pragma once

#include "Foundation.h"
#include "characters/enemies/Enemy.h"


namespace Game {

class ForestDemon final: public Enemy {
public:
    ForestDemon(
        Int maxHealth,
        const Model& model,
        const Configuration& configuration,
        const Point& location,
        Int attackDamage
    );
};

}
