#include "Foundation.h"

#include <gtest/gtest.h>
#include <iostream>


Int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    Int gtestReturnCode = RUN_ALL_TESTS();

    std::cout << "GTest return code: " << gtestReturnCode << std::endl;

    return 0;
}
