#include "Character.h"

using namespace Game;


Character::Character(
    Int maxHealth,
    const Model& model,
    Double movementSpeed,
    const Point& location
):
    _health(maxHealth),
    _model(model),
    _movementSpeed(movementSpeed),
    _location(location),
    _items()
{}

Character::~Character() {
    despawn();
}

Int Character::health() const {
    return _health.value();
}

const Point& Character::location() const {
    return _location;
}

Model& Character::model() {
    return _model;
}

Void Character::spawn() {
    Renderer::shared().addModelToDrawQueue(
        _model,
        _model.texture.isOpaque() ? 1 : IntMax - _location.y
    );
}

Void Character::despawn() {
    Renderer::shared().removeModelFromDrawQueue(_model);
}

Void Character::die() {
    despawn();
}

Void Character::addItem(Item& item) {
    _items.emplace_back(&item);
}

Void Character::removeItem(Item& item) {
    for (auto itr = _items.begin(); itr != _items.end(); ++itr) {
        if (*itr != &item) continue;

        _items.erase(itr);

        return;
    }
}

Void Character::setHealth(Int value) {
    _health.setValue(value);

    if (_health.value() == 0) {
        die();
    }
}

Void Character::increaseHealthBy(Int amount) {
    _health.increaseBy(amount);

    if (_health.value() == 0) {
        die();
    }
}

Void Character::decreaseHealthBy(Int amount) {
    _health.decreaseBy(amount);

    if (_health.value() == 0) {
        die();
    }
}

Void Character::moveTo(const Point& location) {
    _model.moveToXZ(
        _model.position().x + location.x - _location.x,
        _model.position().z + location.y - _location.y,
        _movementSpeed * Point::distanceBetween(location, _location)
    );
    _location = location;
}
