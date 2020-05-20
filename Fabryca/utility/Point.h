#pragma once

#include "Foundation.h"


struct Point {
public:
    Int x = 0;
    Int y = 0;


    Point(Int x = 0, Int y = 0);


    Double distanceToOrigin() const;

    Point& operator+= (const Point& point);
    Point operator+ (const Point& point) const;
    Point& operator-= (const Point& point);
    Point operator- (const Point& point) const;

    Point operator- () const;

    Bool operator== (const Point& point) const;
    Bool operator!= (const Point& point) const;

    static Double distanceBetween(const Point& a, const Point& b);
    static Int manhattanDistanceBetween(const Point& a, const Point& b);
};
