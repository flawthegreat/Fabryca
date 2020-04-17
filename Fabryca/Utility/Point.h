#pragma once

#include "Foundation.h"


struct Point {
public:
    Int x = 0;
    Int y = 0;


    Bool operator== (const Point& point) const;

    static Int distanceBetween(const Point& a, const Point& b);
};
