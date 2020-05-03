#include "PoisonousMonster.h"


PoisonousMonster::PoisonousMonster(
    const std::string& name,
    Int maxHealth,
    const NumericAttribute& attackDamage
):
    Enemy(name, maxHealth, attackDamage, Enemy::Type::poisonousMonster)
{}

Void PoisonousMonster::attackCharacter(Character& character) const {
    Int damage = 0;

    if (Point::distanceBetween(_location, character.location()) <= 1) {
        damage = _attackDamage.value();
    }

    character.decreaseHealthBy(damage);
}

Void PoisonousMonster::setLocation(const Point& location) {
//    _clearPoison();
    _location = location;
//    _poisonLand();
}

Void PoisonousMonster::moveTo(const Point& location) {
//    _clearPoison();
    _location = location;
//    _poisonLand();
}
