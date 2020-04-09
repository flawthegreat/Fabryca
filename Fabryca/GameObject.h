#pragma once

#include "Foundation.h"


class GameObject {
public:
    GameObject();
    virtual ~GameObject() {};


    UInt id() const;

private:
    UInt _id;

    static UInt _freeID;
};
