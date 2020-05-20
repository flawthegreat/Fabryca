#include "Enemy.h"
#include "utility/Random.h"

#include "characters/enemies/ForestDemon.h"
#include "characters/enemies/HoveringBeast.h"
#include "characters/enemies/PoisonousMonster.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace Game;


Enemy::Enemy(
    Int maxHealth,
    const Model& model,
    const Configuration& configuration,
    const Point& location,
    Int attackDamage
):
    Character(maxHealth, model, configuration, location),
    _attackDamage(attackDamage)
{}

Enemy* Enemy::create(
    const Configuration& gameConfiguration,
    Type type,
    Strength strength,
    const Point& location
) {
    Int _type = static_cast<Int>(type);
    Int _strength = static_cast<Int>(strength);

    Int attackDamage = Random::valueInRange(
        gameConfiguration.settings()["enemies"][_type]["stats"][_strength]["minAttackDamage"].asInt(),
        gameConfiguration.settings()["enemies"][_type]["stats"][_strength]["maxAttackDamage"].asInt()
    );
    Int maxHealth = Random::valueInRange(
        gameConfiguration.settings()["enemies"][_type]["stats"][_strength]["minMaxHealth"].asInt(),
        gameConfiguration.settings()["enemies"][_type]["stats"][_strength]["maxMaxHealth"].asInt()
    );
    const Model& model = *gameConfiguration.models().at(
        gameConfiguration.settings()["enemies"][_type]["model"].asString()
    );


    switch (type) {
    case Type::forestDemon:
        return new ForestDemon(
            maxHealth,
            model,
            gameConfiguration,
            location,
            attackDamage
        );
    case Type::hoveringBeast:
        return new HoveringBeast(
            maxHealth,
            model,
            gameConfiguration,
            location,
            attackDamage
        );
    case Type::poisonousMonster:
        return new PoisonousMonster(
            maxHealth,
            model,
            gameConfiguration,
            location,
            attackDamage
        );
    default:
        throw std::runtime_error("Unknown enemy type.");
    }

    return nullptr;
}

Void Enemy::attackCharacter(Character& character) const {
    character.decreaseHealthBy(_attackDamage);
}
