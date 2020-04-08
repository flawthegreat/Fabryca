#include "GameObject.h"


UInt GameObject::_freeID = 1;

GameObject::GameObject() {
    assert(_freeID < UIntMax);

    _id = _freeID++;
}

UInt GameObject::id() const {
    return _id;
}
