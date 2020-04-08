#ifndef HoveringBeast_h
#define HoveringBeast_h

#include "Foundation.h"
#include "Characters/Enemies/Enemy.h"


class HoveringBeast final: public Enemy {
public:
    HoveringBeast(const std::string& name, Int maxHealth, NumericAttribute attackDamage);

    
    Void attackCharacter(Character& character) const override;
};


#endif /* HoveringBeast_h */
