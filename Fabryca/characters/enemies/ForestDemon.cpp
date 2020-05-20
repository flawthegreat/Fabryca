#include "ForestDemon.h"

using namespace Game;


ForestDemon::ForestDemon(
    Int maxHealth,
    const Model& model,
    Double movementSpeed,
    const Point& location,
    Int attackDamage
):
    Enemy(maxHealth, model, movementSpeed, location, attackDamage)
{}

Void ForestDemon::attackCharacter(Character& character) const {
    Int damage = 0;

    if (Point::manhattanDistanceBetween(_location, character.location()) <= 1) {
        damage = _attackDamage;
    }

    character.decreaseHealthBy(damage);
}
