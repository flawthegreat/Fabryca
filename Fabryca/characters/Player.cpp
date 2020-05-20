#include "Player.h"

using namespace Game;


Player::Player(const Configuration& configuration):
    Character(
        configuration.settings()["player"]["maxHealth"].asInt(),
        *configuration.models().at("player"),
        configuration,
        {
            configuration.settings()["constants"]["startLocation"][0].asInt(),
            configuration.settings()["constants"]["startLocation"][1].asInt()
        }
    ),
    _sword(*configuration.models().at("sword")),
    _attackDamage(configuration.settings()["player"]["attackDamage"].asInt())
{
    _setupSword();
}

Void Player::spawn() {
    Character::spawn();
    _sword.show();
}

Void Player::despawn() {
    Character::despawn();
    _sword.hide();
}

Void Player::die() {
    _skull.show();
    Renderer::shared().addAnimationToQueue(
        Animation::Type::scale,
        _skull,
        { 3, 3, 3 },
        _iconAnimationDuration
    );
    Renderer::shared().addAnimationToQueue(
        Animation::Type::move,
        _skull,
        { 0, 3, 3.5 },
        _iconAnimationDuration
    );
    const Float angle = atan2(
        Renderer::shared().camera().position().y,
        Renderer::shared().camera().position().z
    );
    Renderer::shared().addAnimationToQueue(
        Animation::Type::rotate,
        _skull,
        { -angle * 180.0f / M_PI, 0, 0 },
        _iconAnimationDuration
    );

    _postEvent("die");
}

Void Player::attackCharacter(Character& character) const {
    _playAttackAnimation();
    character.decreaseHealthBy(_attackDamage);
}

Void Player::_setupSword() {
    _sword.setScale(0.5);
    _sword.setPosition(0.28, 0.45, 0.01);
    _sword.setZRotation(-12);
    _model.addChild(_sword);
}

Void Player::_playAttackAnimation() const {
    Renderer::shared().addAnimationToQueue(
        Animation::Type::rotate,
        _sword,
        { 0, 0, -100 },
        _iconAnimationDuration / 4,
        [&](Bool) {
            Renderer::shared().addAnimationToQueue(
                Animation::Type::rotate,
                _sword,
                { 0, 0, -12 },
                _iconAnimationDuration / 4
            );
        }
    );
}
