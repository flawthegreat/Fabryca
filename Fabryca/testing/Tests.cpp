#include "Foundation.h"
#include "graphics/WindowManager.h"
#include "utility/Filepath.h"

#include <gtest/gtest.h>
#include <iostream>


Int main(int argc, char **argv) {
    Filepath::setRootFilepath(argc > 1 ? argv[1] : "resources");

    ::testing::InitGoogleTest(&argc, argv);

    WindowManager::shared().initWindow({ 640, 480 }, "Fabryca");

    return RUN_ALL_TESTS();
}
