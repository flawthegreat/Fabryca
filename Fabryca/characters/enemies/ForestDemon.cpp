#include "ForestDemon.h"

using namespace Game;


ForestDemon::ForestDemon(
    Int maxHealth,
    const Model& model,
    const Configuration& configuration,
    const Point& location,
    Int attackDamage
):
    Enemy(maxHealth, model, configuration, location, attackDamage)
{}
