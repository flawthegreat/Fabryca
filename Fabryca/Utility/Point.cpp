#include "Point.h"


Bool Point::operator== (const Point& point) const {
    return x == point.x && y == point.y;
}

Int Point::distanceBetween(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
