#pragma once

#include "Foundation.h"
#include "Characters/Character.h"


class Enemy: public Character {
public:
    enum class Type;
    enum class Strength;


    Enemy(
        const std::string& name,
        Int maxHealth,
        const NumericAttribute& attackDamage,
        Type type
    );
    virtual ~Enemy() {};


    static Enemy* create(Type type, Strength strength);
    
    Type type() const;
    Int attackDamage() const;

    Void setHealth(Int value) override;
    Void increaseHealthBy(Int amount) override;
    Void decreaseHealthBy(Int amount) override;

    virtual Void attackCharacter(Character& character) const = 0;

    Void moveTo(const Point& location) override;

protected:
    const Type _type;
    NumericAttribute _attackDamage;
};


enum class Enemy::Type {
    forestDemon = 0,
    hoveringBeast = 1,
    poisonousMonster = 2,
    _none
};


enum class Enemy::Strength {
    weak = 0,
    dangerous = 1,
    superior = 2,
    _none
};
