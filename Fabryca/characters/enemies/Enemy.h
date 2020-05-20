#pragma once

#include "Foundation.h"
#include "characters/Character.h"
#include "utility/Point.h"
#include "utility/JSON.h"


namespace Game {

class Enemy: public Character {
public:
    enum class Type;
    enum class Strength;


    Enemy(
        Int maxHealth,
        const Model& model,
        const Configuration& configuration,
        const Point& location,
        Int attackDamage
    );


    static Enemy* create(
        const Configuration& gameConfiguration,
        Type type,
        Strength strength,
        const Point& location
    );

    Void attackCharacter(Character& character) const override;

protected:
    const Int _attackDamage;
};


enum class Enemy::Type {
    forestDemon = 0,
    hoveringBeast = 1,
    poisonousMonster = 2,
    none
};


enum class Enemy::Strength {
    weak = 0,
    dangerous = 1,
    superior = 2,
    none
};

}
