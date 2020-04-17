#include "Utility/Point.h"
#include "Utility/NumericAttribute.h"
#include "Utility/Random.h"

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>


TEST(PointTest, Equality) {
    for (Int x1 = -10; x1 <= 10; ++x1) {
        for (Int y1 = -10; y1 <= 10; ++y1) {
            for (Int x2 = -10; x2 <= 10; ++x2) {
                for (Int y2 = -10; y2 <= 10; ++y2) {
                     Bool equal = ((x1 == x2) && (y1 == y2));

                     Point a = { x1, y1 };
                     Point b = { x2, y2 };

                     EXPECT_EQ(equal, a == b);
                }
            }
        }
    }
}

TEST(NumericAttributeTest, ValueChanges) {
    for (Int leftBound = -100; leftBound <= 100; ++leftBound) {
        for (Int rightBound = leftBound; rightBound <= 100; ++rightBound) {
            for (Int value = leftBound; value <= rightBound; ++value) {
                NumericAttribute na(leftBound, rightBound, value);
                na.increaseBy(-20);
                EXPECT_TRUE(na.value() == value - 20 || na.value() == leftBound);

                na = NumericAttribute(leftBound, rightBound, value);
                na.decreaseBy(-30);
                EXPECT_TRUE(na.value() == value + 30 || na.value() == rightBound);

                if (value + 17 <= rightBound) {
                    na = NumericAttribute(leftBound, rightBound, value);
                    na.increaseBy(17);
                    na.decreaseBy(17);
                    EXPECT_TRUE(na.value() == value);
                }

                na = NumericAttribute(leftBound, rightBound, value);
                na.setValue(value + 37);
                EXPECT_TRUE(na.value() == value + 37 || na.value() == rightBound);
            }
        }
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
