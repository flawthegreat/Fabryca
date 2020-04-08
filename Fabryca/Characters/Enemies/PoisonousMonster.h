#ifndef PoisonousMonster_h
#define PoisonousMonster_h

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class PoisonousMonster final: public Enemy {
public:
    PoisonousMonster(const std::string& name, Int maxHealth, NumericAttribute attackDamage);


    Void attackCharacter(Character& character) const override;

    Void setLocation(Point location) override;
    Void moveTo(Point location) override;

private:
    // TODO: Void _poisonLand();
    // TODO: Void _clearPoison();
};


#endif /* PoisonousMonster_h */
