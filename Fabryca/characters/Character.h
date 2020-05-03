#pragma once

#include "Foundation.h"
#include "GameObject.h"
#include "Utility/NumericAttribute.h"
#include "Utility/Point.h"

#include <vector>
#include <string>


class Character: public GameObject {
public:
    Character(
        const std::string& name,
        Int maxHealth,
        const Point& location = { 0, 0 },
        Bool isPeaceful = false
    );
    virtual ~Character() {};


    const std::string& name() const;
    Int health() const;
    const Point& location() const;
    Bool isPeaceful() const;

    virtual Void setHealth(Int value);
    virtual Void increaseHealthBy(Int amount);
    virtual Void decreaseHealthBy(Int amount);

    virtual Void setLocation(const Point& location);
    virtual Void moveTo(const Point& location) = 0;

    // TODO: spawn, despawn, die когда будет игровой мир

protected:
    std::string _name;
    NumericAttribute _health;
    Point _location;
    const Bool _isPeaceful;
};
