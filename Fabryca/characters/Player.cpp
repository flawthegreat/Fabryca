#include "Player.h"

using namespace Game;


Player::Player(
    Int maxHealth,
    const Model& model,
    Double movementSpeed,
    const Point& location
):
    Character(maxHealth, model, movementSpeed, location)
{}

Void Player::attackCharacter(Character& character) const {
    Int damage = 0;

    // TODO:
    // if (Point::distanceBetween(_location, character.location()) <= 1) {
    //     damage = _shortDistanceWeapon ? _shortDistanceWeapon->damage() : 1;
    //  } else if (_longDistanceWeapon) {
    //      damage = _longDistanceWeapon->damage();
    //  }

    character.decreaseHealthBy(damage);
}
