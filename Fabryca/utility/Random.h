#pragma once

#include "Foundation.h"

#include <vector>


namespace Random {

const Int maxValue = Int32Max;

Void reset();
Int value();
Int valueInRange(Int leftBound, Int rightBound);

}
