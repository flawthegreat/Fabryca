#include "GameInstance.h"

#include <gtest/gtest.h>
#include <iostream>

using namespace Game;


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
