#include "Point.h"

#include <cmath>


Point::Point(Int x, Int y):
    x(x),
    y(y)
{}

Double Point::distanceToOrigin() const {
    Double _x = static_cast<Double>(x);
    Double _y = static_cast<Double>(y);

    return sqrt(_x * _x + _y * _y);
}

Point& Point::operator+= (const Point& point) {
    x += point.x;
    y += point.y;

    return *this;
}

Point Point::operator+ (const Point& point) const {
    Point copy = *this;
    copy += point;

    return copy;
}

Point& Point::operator-= (const Point& point) {
    x -= point.x;
    y -= point.y;

    return *this;
}

Point Point::operator- (const Point& point) const {
    Point copy = *this;
    copy -= point;

    return copy;
}

Point Point::operator- () const {
    return { -x, -y };
}

Bool Point::operator== (const Point& point) const {
    return x == point.x && y == point.y;
}

Bool Point::operator!= (const Point& point) const {
    return !(*this == point);
}

Double Point::distanceBetween(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Int Point::manhattanDistanceBetween(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
