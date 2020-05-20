#include "HoveringBeast.h"

using namespace Game;


HoveringBeast::HoveringBeast(
    Int maxHealth,
    const Model& model,
    Double movementSpeed,
    const Point& location,
    Int attackDamage
):
    Enemy(maxHealth, model, movementSpeed, location, attackDamage)
{}

Void HoveringBeast::attackCharacter(Character& character) const {
    Int damage = 0;

    if (Point::manhattanDistanceBetween(_location, character.location()) >= 3) {
        damage = _attackDamage;
    }

    character.decreaseHealthBy(damage);
}
