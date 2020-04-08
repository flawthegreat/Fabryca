#include "Human.h"
#include "Constants/HumanConstants.h"
#include "Utility/Random.h"


Human::Human(const std::string& name):
    Character(name, 100, { 0, 0 }, true)
{}

// TODO: игровые предметы
// Void Human::sellItemToPlayer(const Item& item, Player& player) {
//     if (player.money() >= item.price()) {
//         removeItem(item);
//
//         player.decreaseMoneyBy(item.price() * hc);
//         player.addItem(item);
//     }
// }

Void Human::moveTo(Point location) {
    // TODO: когда будет игровой мир
}

Human* Human::create() {
    // TODO: наполнять случайными предметами

    Human* human = new Human(possibleNames[Random::value() % possibleNames.size()]);

    return human;
}
