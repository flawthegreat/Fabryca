#include "HoveringBeast.h"

using namespace Game;


HoveringBeast::HoveringBeast(
    Int maxHealth,
    const Model& model,
    const Configuration& configuration,
    const Point& location,
    Int attackDamage
):
    Enemy(maxHealth, model, configuration, location, attackDamage)
{}
