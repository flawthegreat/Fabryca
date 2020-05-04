#include "utility/Point.h"
#include "utility/NumericAttribute.h"
#include "utility/Random.h"
#include "utility/Filepath.h"

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>


TEST(PointTest, DistanceToOrigin) {
    Point a = { 0, 0 };
    ASSERT_EQ(a.distanceToOrigin(), 0);

    a = { -2, -10 };
    ASSERT_TRUE(a.distanceToOrigin() >= 0);

    a = { 3, 4 };
    ASSERT_TRUE(fabs(a.distanceToOrigin() - 5) <= 1e-12);
}

TEST(PointTest, Distance) {
    const Point a = { 10, -5 };
    const Point b = { -900, 312 };

    ASSERT_EQ(Point::distanceBetween(a, b), sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
    ASSERT_EQ(Point::distanceBetween(a, a), 0);
}

TEST(PointTest, ManhattanDistance) {
    const Point a = { 10, -5 };
    const Point b = { -900, 312 };
    const Int dx = abs(a.x - b.x);
    const Int dy = abs(a.y - b.y);

    ASSERT_EQ(Point::manhattanDistanceBetween(a, b), dx + dy);
}

TEST(PointTest, Operators) {
    Point a = { 30, 10 };
    Point b = -a;
    ASSERT_TRUE(a.x == -b.x && a.y == -b.y);
    ASSERT_EQ(a, -b);

    b = { -8, 49 };
    ASSERT_NE(a, b);

    ASSERT_EQ(a + b, Point(22, 59));
    ASSERT_EQ(a - b, Point(38, -39));

    a += b;
    ASSERT_EQ(a, Point(22, 59));

    a -= b;
    ASSERT_EQ(a, Point(30, 10));
}

TEST(NumericAttributeTest, ValueChanges) {
    NumericAttribute na(-10, 73, 30);

    ASSERT_EQ(na.range(), 83);
    ASSERT_TRUE(fabs(na.percentage() - 0.48192771) < 1e-8);

    na.increaseBy(-20);
    ASSERT_EQ(na.value(), 10);

    na.decreaseBy(-30);
    ASSERT_EQ(na.value(), 40);

    na.increaseBy(10000);
    ASSERT_EQ(na.value(), 73);

    na.decreaseBy(999999);
    ASSERT_EQ(na.value(), -10);

    na.setValue(1);
    ASSERT_EQ(na.value(), 1);

    na.setValue(134);
    ASSERT_EQ(na.value(), 73);

    na.setPercentage(0.8);
    ASSERT_EQ(na.value(), 56);
}

TEST(RandomTest, Values) {
    Int previousValue = -1;

    for (Int i = 0; i < 10000; ++i) {
        Int value = Random::value();

        EXPECT_NE(value, previousValue);

        previousValue = value;
    }
}

TEST(RandomTest, Range) {
    for (Int leftBound = -1000; leftBound <= 1000; ++leftBound) {
        for (Int rightBound = leftBound; rightBound <= 1000; ++rightBound) {
            Int randomValue = Random::valueInRange(leftBound, rightBound);

            EXPECT_LE(randomValue, rightBound);
            EXPECT_GE(randomValue, leftBound);
        }
    }
}
