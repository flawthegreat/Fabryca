#pragma once

#include "Foundation.h"
#include "characters/Character.h"
#include "utility/Point.h"


namespace Game {

class Player final: public Character {
public:
    Player(const Configuration& configuration);


    Void spawn() override;
    Void despawn() override;
    Void die() override;

    Void attackCharacter(Character& character) const override;

private:
    mutable Model _sword;

    const Int _attackDamage;


    Void _setupSword();
    Void _playAttackAnimation() const;
};

}
