#include "Cure.h"


Cure::Cure(Int amount):
    Item(Item::Type::cure, "Cure", "Increases health by " + std::to_string(amount) + "."),
    _amount(amount)
{}

Int Cure::amount() const {
    return _amount;
}

Void Cure::applyEffectToCharacter(Character& character) {
    character.increaseHealthBy(_amount);
}
