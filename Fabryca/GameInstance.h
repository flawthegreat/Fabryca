#pragma once

#include "Foundation.h"
#include "graphics/Graphics.h"
#include "Configuration.h"
#include "Terrain.h"
#include "utility/Filepath.h"

#include <string>
#include <unordered_map>


namespace Game {

class GameInstance final {
public:
    GameInstance(const Filepath& settingsFilepath);


    const Configuration& configuration() const;

    Void processInput();

private:
    Configuration _configuration;
    Terrain _terrain;
};

}
