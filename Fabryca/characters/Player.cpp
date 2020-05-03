#include "Player.h"


Player::Player(const std::string& name):
    Character(name, 100),
    _money(0, 1'000'000),
    _honor(0, 100)
{}

Int Player::money() const {
    return _money.value();
}

Int Player::honor() const {
    return _honor.value();
}

Void Player::setMoney(Int value) {
    _money.setValue(value);
}

Void Player::increaseMoneyBy(Int amount) {
    _money.increaseBy(amount);
}

Void Player::decreaseMoneyBy(Int amount) {
    _money.decreaseBy(amount);
}

Void Player::setHonor(Int value) {
    _honor.setValue(value);
}

Void Player::increaseHonorBy(Int amount) {
    _honor.increaseBy(amount);
}

Void Player::decreaseHonorBy(Int amount) {
    _honor.decreaseBy(amount);
}

Void Player::attackCharacter(Character& character) {
    Int damage = 0;

    // TODO: игровые предметы
    // if (Point::distanceBetween(_location, character.location()) <= 1) {
    //     damage = _shortDistanceWeapon ? _shortDistanceWeapon->damage() : 1;
    //  } else if (_longDistanceWeapon) {
    //      damage = _longDistanceWeapon->damage();
    //  }

    if (character.isPeaceful()) {
        decreaseHonorBy(40);
    } else if (character.health() <= damage) {
        increaseHonorBy(1);
    }

    character.decreaseHealthBy(damage);
}

Void Player::moveTo(const Point& location) {
    // TODO: когда будет игровой мир
}

Player* Player::create(const std::string& name) {
    // TODO: загрузка сохраненного списка предметов, параметров
    return new Player(name);
}
