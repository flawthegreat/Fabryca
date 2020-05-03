#pragma once

#include "Foundation.h"
#include "Object.h"
#include "Configuration.h"
#include "items/Item.h"
#include "utility/NumericAttribute.h"
#include "utility/Point.h"
#include "graphics/Graphics.h"

#include <vector>
#include <string>


namespace Game {

class Item;


class Character: public Object {
public:
    Character(
        Int maxHealth,
        const Model& model,
        Double movementSpeed,
        const Point& location
    );
    Character(const Character&) = delete;
    Character& operator= (const Character&) = delete;
    Character(Character&&) = delete;
    Character& operator= (Character&&) = delete;
    virtual ~Character();


    Int health() const;
    const Point& location() const;
    Model& model();

    virtual Void spawn();
    virtual Void despawn();
    virtual Void die();

    virtual Void addItem(Item& item);
    virtual Void removeItem(Item& item);

    virtual Void setHealth(Int value);
    virtual Void increaseHealthBy(Int amount);
    virtual Void decreaseHealthBy(Int amount);

    virtual Void attackCharacter(Character& character) const = 0;
    
    virtual Void moveTo(const Point& location);

protected:
    NumericAttribute _health;
    Model _model;
    Double _movementSpeed;
    Point _location;
    std::vector<Item*> _items;
};

}
