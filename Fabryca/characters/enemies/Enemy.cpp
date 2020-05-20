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
    Double movementSpeed,
    const Point& location,
    Int attackDamage
):
    Character(maxHealth, model, movementSpeed, location),
    _attackDamage(attackDamage)
{}

Enemy* Enemy::create(
    const Configuration& Configuration,
    Type type,
    Strength strength,
    const Point& location
) {
    Int _type = static_cast<Int>(type);
    Int _strength = static_cast<Int>(strength);

    Int attackDamage = Random::valueInRange(
        Configuration.settings()["enemies"][_type]["stats"][_strength]["minAttackDamage"].asInt(),
        Configuration.settings()["enemies"][_type]["stats"][_strength]["maxAttackDamage"].asInt()
    );
    Int maxHealth = Random::valueInRange(
        Configuration.settings()["enemies"][_type]["stats"][_strength]["minMaxHealth"].asInt(),
        Configuration.settings()["enemies"][_type]["stats"][_strength]["maxMaxHealth"].asInt()
    );
    Double movementSpeed = Configuration.settings()["enemies"][_type]["movementSpeed"].asDouble();
    const Model& model = *Configuration.models().at(
        Configuration.settings()["enemies"][_type]["model"].asString()
    );


    switch (type) {
    case Type::forestDemon:
        return new ForestDemon(
            maxHealth,
            model,
            movementSpeed,
            location,
            attackDamage
        );
    case Type::hoveringBeast:
        return new HoveringBeast(
            maxHealth,
            model,
            movementSpeed,
            location,
            attackDamage
        );
    case Type::poisonousMonster:
        return new PoisonousMonster(
            maxHealth,
            model,
            movementSpeed,
            location,
            attackDamage
        );
    default:
        throw std::runtime_error("Unknown enemy type.");
    }

    return nullptr;
}
