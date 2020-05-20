#include "Foundation.h"
#include "utility/Random.h"
#include "utility/Filepath.h"
#include "GameInstance.h"

#include <iostream>


Int main(Int argc, Char** argv) {
    Filepath::setRootFilepath(argc > 1 ? argv[1] : "resources");

    Random::reset();

    WindowManager& windowManager = WindowManager::shared();
    windowManager.initWindow({ 1200, 675 }, "Fabryca");
    windowManager.setMinimumWindowSize({ 640, 480 });

    Renderer& renderer = Renderer::shared();
    Game::GameInstance game("Settings.json");

    while (!windowManager.windowShouldClose()) {
        game.processInput();

        renderer.processAnimations();
        renderer.draw();

        windowManager.swapBuffers();
        windowManager.pollEvents();
    }

    return 0;
}
