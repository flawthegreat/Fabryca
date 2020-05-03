#pragma once

#include "Foundation.h"
#include "GameObject.h"
#include "Character.h"

#include <string>


class Item: public GameObject {
public:
    enum class Type;
    enum class Rarity;


    Item(Type type, const std::string& name, const std::string& description);
    virtual ~Item() {};


    static Item* create(Type type, Rarity rarity);

    Type type() const;
    const std::string& name() const;
    const std::string& description() const;

    virtual Void applyEffectToCharacter(Character& character) = 0;

private:
    const Type _type;
    std::string _name;
    std::string _description;
};


enum class Item::Type {
    weapon = 0,
    cure = 1,
    key = 2,
    money = 3,
    _none
};


enum class Item::Rarity {
    common = 0,
    rare = 1,
    legendary = 2,
    _none
};
