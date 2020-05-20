#pragma once

#include "Foundation.h"
#include "Object.h"
#include "Configuration.h"
#include "utility/NumericAttribute.h"
#include "utility/Point.h"
#include "utility/EventManager.h"
#include "graphics/Graphics.h"
#include "HealthIndicator.h"

#include <vector>
#include <string>


namespace Game {

class Character: public Object, public EventManager<Character> {
public:
    Character(
        Int maxHealth,
        const Model& model,
        const Configuration& configuration,
        const Point& location
    );

    Character(const Character&) = delete;
    Character& operator= (const Character&) = delete;
    Character(Character&&) = delete;
    Character& operator= (Character&&) = delete;

    virtual ~Character();


    Int health() const;
    Int maxHealth() const;
    const Point& location() const;
    Model& model();

    virtual Void spawn();
    virtual Void despawn();
    virtual Void die();

    virtual Void setHealth(Int value);
    virtual Void increaseHealthBy(Int amount);
    virtual Void decreaseHealthBy(Int amount);

    virtual Void attackCharacter(Character& character) const = 0;
    
    virtual Void moveTo(const Point& location, const Callback& callback = Callback());

protected:
    NumericAttribute _health;
    HealthIndicator _healthIndicator;

    Model _model;
    mutable Model _skull;
    mutable Model _heart;
    Bool _isVisible;

    Point _location;
    Double _iconAnimationDuration;
    Double _moveDuration;


    virtual Void _setupIcon(Model& icon);
    virtual Void _playIconAnimation(Model& icon) const;
};

}
