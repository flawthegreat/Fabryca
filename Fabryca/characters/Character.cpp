#include "Character.h"

using namespace Game;


Character::Character(
    Int maxHealth,
    const Model& model,
    const Configuration& configuration,
    const Point& location
):
    _health(maxHealth),
    _healthIndicator(maxHealth, { 0, 1.5, 0 }, configuration),
    _model(model),
    _skull(*configuration.models().at("skull")),
    _heart(*configuration.models().at("heart")),
    _isVisible(false),
    _location(location),
    _iconAnimationDuration(
        configuration.settings()["constants"]["iconAnimationDuration"].asDouble()
    ),
    _moveDuration(configuration.settings()["constants"]["characterMoveDuration"].asDouble())
{
    _setupIcon(_skull);
    _setupIcon(_heart);

    _model.addChild(_healthIndicator.model());
}

Character::~Character() {
    despawn();
}

Int Character::health() const {
    return _health.value();
}

Int Character::maxHealth() const {
    return _health.maxValue();
}

const Point& Character::location() const {
    return _location;
}

Model& Character::model() {
    return _model;
}

Void Character::spawn() {
    _model.show(IntMax);
    _healthIndicator.show();
    _isVisible = true;
}

Void Character::despawn() {
    _model.hide();
    _healthIndicator.hide();
    _isVisible = false;
}

Void Character::die() {
    _playIconAnimation(_skull);
    despawn();
    _postEvent("die");
}

Void Character::setHealth(Int value) {
    _health.setValue(value);
    _healthIndicator.setValue(value);

    if (_health.value() == 0) { die(); }
}

Void Character::increaseHealthBy(Int amount) {
    _health.increaseBy(amount);
    _healthIndicator.setValue(_health.value());

    if (_health.value() == 0) { die(); }
}

Void Character::decreaseHealthBy(Int amount) {
    _health.decreaseBy(amount);
    _healthIndicator.setValue(_health.value());

    if (_health.value() == 0) {
        die();
    } else {
        _playIconAnimation(_heart);
    }
}

Void Character::moveTo(const Point& location, const Callback& callback) {
    _model.moveToXZ(
        _model.position().x + location.x - _location.x,
        _model.position().z + location.y - _location.y,
        _moveDuration,
        callback
    );
    _location = location;
    _postEvent("move");
}

Void Character::_setupIcon(Model& icon) {
    icon.setScale(0.5);
    icon.setYPosition(0.5);
    icon.setZPosition(0.01);
    _model.addChild(icon);
}

Void Character::_playIconAnimation(Model& icon) const {
    icon.show();
    icon.moveBy(
        { 0, 1, 0 },
        _iconAnimationDuration,
        [&, icon=&icon](Bool) {
            icon->setPosition({ 0, 0.5, 0 });
            icon->hide();
        }
    );
}
