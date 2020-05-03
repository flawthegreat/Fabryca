#include "Random.h"

#include <ctime>


namespace Random {

Void reset() {
    srand(static_cast<Int>(time(0)));
}

Int value() {
    return rand();
}

Int valueInRange(Int leftBound, Int rightBound) {
    assert(leftBound <= rightBound);

    return leftBound + rand() % (rightBound - leftBound + 1);
}

}
