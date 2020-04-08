#ifndef Character_h
#define Character_h

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
        Point location = { 0, 0 },
        Bool isPeaceful = false
    );
    virtual ~Character() {};


    virtual std::string name() const;
    virtual Int health() const;
    virtual Point location() const;
    virtual Bool isPeaceful() const;

    virtual Void setHealth(Int value);
    virtual Void increaseHealthBy(Int amount);
    virtual Void decreaseHealthBy(Int amount);

    virtual Void setLocation(Point location);
    virtual Void moveTo(Point location) = 0;

    // TODO: spawn, despawn, die когда будет игровой мир

protected:
    std::string _name;
    NumericAttribute _health;
    Point _location;
    const Bool _isPeaceful;
};


#endif /* Character_h */
