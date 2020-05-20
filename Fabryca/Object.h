#pragma once

#include "Foundation.h"


namespace Game {

class Object {
public:
    Object();
    virtual ~Object() {};


    UInt id() const;

protected:
    const UInt _id;

private:
    static UInt _freeID;
};

}
