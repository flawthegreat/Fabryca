#ifndef Point_h
#define Point_h

#include "Foundation.h"


struct Point {
public:
    Int x = 0;
    Int y = 0;


    Bool operator== (const Point& point) const;

    static Int distanceBetween(const Point& a, const Point& b);
};


#endif /* Point_h */
