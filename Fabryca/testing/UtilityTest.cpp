#include "utility/Point.h"
#include "utility/NumericAttribute.h"
#include "utility/Random.h"

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>


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
