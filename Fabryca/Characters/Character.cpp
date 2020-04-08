#include "Character.h"


Character::Character(const std::string& name, Int maxHealth, Point location, Bool isPeaceful):
    _name(name),
    _health(0, maxHealth, maxHealth),
    _location(location),
    _isPeaceful(isPeaceful)
{
    assert(maxHealth > 0);
}

std::string Character::name() const {
    return _name;
}

Int Character::health() const {
    return _health.value();
}

Point Character::location() const {
    return _location;
}

Bool Character::isPeaceful() const {
    return _isPeaceful;
}

Void Character::setHealth(Int value) {
    _health.setValue(value);

    if (_health.value() == 0) {
        // TODO: умирает (когда будет игровой мир)
    }
}

Void Character::increaseHealthBy(Int amount) {
    _health.increaseBy(amount);

    if (_health.value() == 0) {
        // TODO: умирает (когда будет игровой мир)
    }
}

Void Character::decreaseHealthBy(Int amount) {
    _health.decreaseBy(amount);

    if (_health.value() == 0) {
        // TODO: умирает (когда будет игровой мир)
    }
}

Void Character::setLocation(Point location) {
    _location = location;
}
