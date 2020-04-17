#include "Enemy.h"
#include "Constants/EnemyConstants.h"
#include "Utility/Random.h"

#include "Characters/Enemies/ForestDemon.h"
#include "Characters/Enemies/HoveringBeast.h"
#include "Characters/Enemies/PoisonousMonster.h"

#include <iostream>
#include <string>


Enemy::Enemy(
    const std::string& name,
    Int maxHealth,
    const NumericAttribute& attackDamage,
    Type type
):
    Character(name, maxHealth),
    _type(type),
    _attackDamage(attackDamage)
{}

Enemy::Type Enemy::type() const {
    return _type;
}

Int Enemy::attackDamage() const {
    return _attackDamage.value();
}

Void Enemy::setHealth(Int value) {
    _health.setValue(value);
    _attackDamage.setPercentage(_health.percentage());
}

Void Enemy::increaseHealthBy(Int amount) {
    _health.increaseBy(amount);
    _attackDamage.setPercentage(_health.percentage());
}

Void Enemy::decreaseHealthBy(Int amount) {
    _health.decreaseBy(amount);
    _attackDamage.setPercentage(_health.percentage());
}

Void Enemy::moveTo(const Point& location) {
    // TODO: когда будет игровой мир
}

Enemy* Enemy::create(Enemy::Type type, Enemy::Strength strength) {
    std::string name = possibleNames[Random::value() % possibleNames.size()];

    // TODO: наполнять случайными предметами

    Int _type = static_cast<Int>(type);
    Int _strength = static_cast<Int>(strength);

    Int maxHealth = Random::valueInRange(
        parameters[_type][_strength][0].minValue(),
        parameters[_type][_strength][0].maxValue()
    );
    Int maxDamage = Random::valueInRange(
        parameters[_type][_strength][1].minValue(),
        parameters[_type][_strength][1].maxValue()
    );

    NumericAttribute damage = NumericAttribute(maxDamage / 2 + maxDamage % 1, maxDamage, maxDamage);

    switch (type) {
    case Type::forestDemon:
        return new ForestDemon(name, maxHealth, damage);
    case Type::hoveringBeast:
        return new HoveringBeast(name, maxHealth, damage);
    case Type::poisonousMonster:
        return new PoisonousMonster(name, maxHealth, damage);
    default:
        std::cerr << "[Uknown enemy type]" << std::endl;
        assert(false);

        return nullptr;
    }
}

