#pragma once

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class PoisonousMonster final: public Enemy {
public:
    PoisonousMonster(const std::string& name, Int maxHealth, const NumericAttribute& attackDamage);


    Void attackCharacter(Character& character) const override;

    Void setLocation(const Point& location) override;
    Void moveTo(const Point& location) override;

private:
    // TODO: Void _poisonLand();
    // TODO: Void _clearPoison();
};
