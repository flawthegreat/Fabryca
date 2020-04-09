#include "ForestDemon.h"


ForestDemon::ForestDemon(
    const std::string& name,
    Int maxHealth,
    const NumericAttribute& attackDamage
):
    Enemy(name, maxHealth, attackDamage, Enemy::Type::forestDemon)
{}

Void ForestDemon::attackCharacter(Character& character) const {
    Int damage = 0;

    if (Point::distanceBetween(_location, character.location()) <= 1) {
        damage = _attackDamage.value();
    }

    character.decreaseHealthBy(damage);
}
