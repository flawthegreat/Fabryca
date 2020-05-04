#include "Foundation.h"
#include "utility/Random.h"
#include "utility/Filepath.h"
#include "GameInstance.h"

#include <iostream>


/*

Соотношение сторон Ubuntu

 */


Int main(Int argc, Char** argv) {
    Filepath::setRootFilepath(argc > 1 ? argv[1] : "resources");

    Random::reset();

    // Позже все константы уедут в файл настроек, большинство кода отсюда окажется в GameInstance

    WindowManager& windowManager = WindowManager::shared();
    windowManager.initWindow({ 1200, 675 }, "Fabryca");
    windowManager.setMinimumWindowSize({ 640, 480 });

    Renderer& renderer = Renderer::shared();

    renderer.setClearColor(glm::vec4(1.0f));
    renderer.setCameraFocusPoint(0, 0, 0);
    renderer.setCameraPosition(0, 8, 11);

    renderer.setLightPosition(-2, 0, 2);
    renderer.setLightDirection(1, -1, -1);
    renderer.setLightPower(0.62f);

    renderer.setViewDistance(30);

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
