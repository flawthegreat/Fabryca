#ifndef Enemy_h
#define Enemy_h

#include "Foundation.h"
#include "Characters/Character.h"


class Enemy: public Character {
public:
    enum class Type;
    enum class Strength;


    Enemy(
        const std::string& name,
        Int maxHealth,
        NumericAttribute attackDamage,
        Type type
    );
    virtual ~Enemy() {};


    virtual Type type() const;
    virtual Int attackDamage() const;

    Void setHealth(Int value) override;
    Void increaseHealthBy(Int amount) override;
    Void decreaseHealthBy(Int amount) override;

    virtual Void attackCharacter(Character& character) const = 0;

    Void moveTo(Point location) override;

    static Enemy* create(Type type, Strength strength);

protected:
    const Type _type;
    NumericAttribute _attackDamage;
};


enum class Enemy::Type {
    forestDemon = 0,
    hoveringBeast = 1,
    poisonousMonster = 2,
    _none = 3
};


enum class Enemy::Strength {
    weak = 0,
    dangerous = 1,
    superior = 2,
    _none = 3
};


#endif /* Enemy_h */
