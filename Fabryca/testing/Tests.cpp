#include "Foundation.h"
#include "graphics/WindowManager.h"

#include <gtest/gtest.h>
#include <iostream>


Int main(int argc, char **argv) {
    if (argc > 1) {
        resourcesPath = argv[1];
    }

    ::testing::InitGoogleTest(&argc, argv);

    WindowManager::shared().initWindow({ 640, 480 }, "Fabryca");

    std::cout << resourcesPath << std::endl;

    return RUN_ALL_TESTS();
}
