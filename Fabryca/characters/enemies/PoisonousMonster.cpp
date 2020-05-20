#include "PoisonousMonster.h"

using namespace Game;


PoisonousMonster::PoisonousMonster(
    Int maxHealth,
    const Model& model,
    const Configuration& configuration,
    const Point& location,
    Int attackDamage
):
    Enemy(maxHealth, model, configuration, location, attackDamage)
{}
