#ifndef Human_h
#define Human_h

#include "Foundation.h"
#include "Characters/Character.h"
#include "Characters/Player.h"

#include <string>


class Human final: public Character {
public:
    Human(const std::string& name);


    // TODO: игровые предметы
    // Void sellItemToPlayer(const Item& item, Player& player);
    Void moveTo(Point location) override;

    static Human* create();
};


#endif /* Human_h */
