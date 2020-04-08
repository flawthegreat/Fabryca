#ifndef ForestDemon_h
#define ForestDemon_h

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class ForestDemon final: public Enemy {
public:
    ForestDemon(const std::string& name, Int maxHealth, NumericAttribute attackDamage);


    Void attackCharacter(Character& character) const override;
};


#endif /* ForestDemon_h */
