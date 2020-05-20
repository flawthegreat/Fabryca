#include "Object.h"

#include <stdexcept>

using namespace Game;


UInt Object::_freeID = 1;

Object::Object():
    _id(_freeID++)
{
    if (_freeID == 0) throw std::runtime_error("No Object IDs left.");
}

UInt Object::id() const {
    return _id;
}
