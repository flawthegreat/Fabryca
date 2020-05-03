#include "Item.h"

#include <stdexcept>


Item::Item(Type type, const std::string& name, const std::string& description):
    _type(type),
    _name(name),
    _description(description)
{}

Item* Item::create(Type type, Rarity rarity) {
    // TODO: fuck
    static_assert(false);
};

Item::Type Item::type() const {
    return _type;
}

const std::string& Item::name() const {
    return _name;
}

const std::string& Item::description() const {
    return _description;
}
