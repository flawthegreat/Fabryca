#include "HoveringBeast.h"


HoveringBeast::HoveringBeast(
    const std::string& name,
    Int maxHealth,
    NumericAttribute attackDamage
):
    Enemy(name, maxHealth, attackDamage, Enemy::Type::hoveringBeast)
{}

Void HoveringBeast::attackCharacter(Character& character) const {
    Int damage = 0;

    if (Point::distanceBetween(_location, character.location()) >= 3) {
        damage = _attackDamage.value();
    }

    character.decreaseHealthBy(damage);
}
