#include "Foundation.h"
#include "characters/Player.h"
#include "characters/enemies/Enemy.h"

#include "characters/enemies/ForestDemon.h"
#include "characters/enemies/HoveringBeast.h"
#include "characters/enemies/PoisonousMonster.h"

#include <gtest/gtest.h>

using namespace Game;


Point randomPoint() {
    return { rand(), rand() };
}

TEST(PlayerTest, CreationAndMethods) {
    const Int maxHealth = rand();
    const Point location = randomPoint();

    Player* player = new Player(
        maxHealth,
        Model(
            "meshes/character.obj",
            "textures/player.bt",
            "shaders/basic"
        ),
        1,
        location
    );

    ASSERT_TRUE(player != nullptr);

    EXPECT_TRUE(player->health() == maxHealth);
    EXPECT_TRUE(player->location() == location);

    const Int healthDrop = rand() % maxHealth;
    player->decreaseHealthBy(healthDrop);

    EXPECT_TRUE(player->health() == maxHealth - healthDrop);

    player->increaseHealthBy(healthDrop);
    EXPECT_TRUE(player->health() == maxHealth);

    player->setHealth(maxHealth / 2);
    EXPECT_TRUE(player->health() == maxHealth / 2);

    const Point newLocation = randomPoint();
    player->moveTo(newLocation);

    EXPECT_TRUE(player->location() == newLocation);

//  TODO:
//    const Int currentHealth = player->health();
//    player->attackCharacter(*player);
//
//    EXPECT_TRUE(player->health() == currentHealth - attackDamage);

    player->spawn();
    player->despawn();

    delete player;
}

TEST(EnemyTest, Creation) {
    Configuration config("Settings.json");

    for (Int _type = 0; _type < static_cast<Int>(Enemy::Type::none); ++_type) {
        for (Int _strength = 0; _strength < static_cast<Int>(Enemy::Strength::none); ++_strength) {
            Enemy::Type type = static_cast<Enemy::Type>(_type);
            Enemy::Strength strength = static_cast<Enemy::Strength>(_strength);

            Enemy* enemy = Enemy::create(config, type, strength, randomPoint());

            ASSERT_TRUE(enemy != nullptr);

            switch (type) {
            case Enemy::Type::forestDemon:
                EXPECT_TRUE(dynamic_cast<ForestDemon*>(enemy) != nullptr);
                break;
            case Enemy::Type::hoveringBeast:
                EXPECT_TRUE(dynamic_cast<HoveringBeast*>(enemy) != nullptr);
                break;
            case Enemy::Type::poisonousMonster:
                EXPECT_TRUE(dynamic_cast<PoisonousMonster*>(enemy) != nullptr);
                break;
            default:
                EXPECT_TRUE(false);
            }

            delete enemy;
        }
    }
}
