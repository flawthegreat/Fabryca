#include "Weapon.h"

using namespace Game;


Weapon::Weapon(const Model& model, Range range, Int damage):
    Item(model),
    _range(range),
    _damage(damage)
{}

Int Weapon::damage() const {
    return _damage;
}

Void Weapon::applyEffectToCharacter(Character& character) {
    character.decreaseHealthBy(_damage);
}
