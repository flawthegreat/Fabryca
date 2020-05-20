#pragma once

#include "Foundation.h"
#include "characters/Character.h"
#include "utility/Point.h"


namespace Game {

class Player final: public Character {
public:
    Player(
        Int maxHealth,
        const Model& model,
        Double movementSpeed = 1,
        const Point& location = { 0, 0 }
    );


    Void attackCharacter(Character& character) const override;
};

}
