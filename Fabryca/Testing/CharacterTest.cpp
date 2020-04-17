#include "Foundation.h"
#include "Characters/Human.h"
#include "Characters/Enemies/Enemy.h"

#include "Characters/Enemies/ForestDemon.h"
#include "Characters/Enemies/HoveringBeast.h"
#include "Characters/Enemies/PoisonousMonster.h"

#include <gtest/gtest.h>


TEST(HumanTest, Creation) {
    Human* human = Human::create();

    EXPECT_TRUE(human != nullptr);

    delete human;
}

TEST(EnemyTest, Creation) {
    for (Int _type = 0; _type < static_cast<Int>(Enemy::Type::_none); ++_type) {
        for (Int _strength = 0; _strength < static_cast<Int>(Enemy::Strength::_none); ++_strength) {
            Enemy::Type type = static_cast<Enemy::Type>(_type);
            Enemy::Strength strength = static_cast<Enemy::Strength>(_strength);

            Enemy* enemy = Enemy::create(type, strength);

            ASSERT_TRUE(enemy != nullptr);
            EXPECT_TRUE(enemy->type() == type);

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
