#include "Object.h"
#include "GameInstance.h"
#include "Terrain.h"

#include <gtest/gtest.h>
#include <iostream>

using namespace Game;


TEST(ObjectTest, IDUniqueness) {
    UInt previousID = 0;

    for (Int i = 0; i < 1'000'000; ++i) {
        const Object object;

        ASSERT_NE(object.id(), previousID);

        previousID = object.id();
    }
}

TEST(GameInstanceTest, Creation) {
    GameInstance game("Settings.json");

    Terrain terrain({ 30, 49 }, game.configuration());

    const Direction direction = static_cast<Direction>(rand() % 4);
    Point cursorLocation = terrain.cursor().location;
    switch (direction) {
    case Direction::up:
        cursorLocation += { 0, -1 };
        break;
    case Direction::down:
        cursorLocation += { 0, 1 };
        break;
    case Direction::right:
        cursorLocation += { 1, 0 };
        break;
    case Direction::left:
        cursorLocation += { -1, 0 };
        break;
    default:
        ASSERT_TRUE(false);
    }

    terrain.shiftCursor(direction);
    ASSERT_TRUE(terrain.cursor().location == cursorLocation);
}
