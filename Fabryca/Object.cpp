#include "Object.h"

#include <stdexcept>


UInt GameObject::_freeID = 1;

GameObject::GameObject():
    _id(_freeID++)
{
    if (_freeID == 0) {
        throw std::runtime_error("No GameObject IDs left.");
    }
}

UInt GameObject::id() const {
    return _id;
}
