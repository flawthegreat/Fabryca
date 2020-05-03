#include "CureItem.h"

using namespace Game;


CureItem::CureItem(const Model& model, Int healthAmount):
    Item(model),
    _healthAmount(healthAmount)
{}

Int CureItem::healthAmount() const {
    return _healthAmount;
}

Void CureItem::applyEffectToCharacter(Character& character) {
    character.increaseHealthBy(_healthAmount);
}
