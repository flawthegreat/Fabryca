#pragma once

#include "Foundation.h"
#include "Characters/Character.h"

#include <string>


class Player final: public Character {
public:
    Player(const std::string& name);


    static Player* create(const std::string& name);
    
    Int money() const;
    Int honor() const;

    Void setMoney(Int value);
    Void increaseMoneyBy(Int amount);
    Void decreaseMoneyBy(Int amount);

    Void setHonor(Int value);
    Void increaseHonorBy(Int amount);
    Void decreaseHonorBy(Int amount);

    Void attackCharacter(Character& character);

    Void moveTo(const Point& location) override;

private:
    NumericAttribute _money;
    NumericAttribute _honor;
};
