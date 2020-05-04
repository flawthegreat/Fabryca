#include "GameInstance.h"

#include <stdexcept>

using namespace Game;


GameInstance::GameInstance(const Filepath& settingsFilepath):
    _configuration(settingsFilepath),
    _terrain({ 15, 18 }, _configuration)
{
    // TODO: сохранения
}

const Configuration& GameInstance::configuration() const {
    return _configuration;
}

Void GameInstance::processInput() {
    if (WindowManager::shared().keyWasPressed(Key::d)) {
        _terrain.shiftCursor(Direction::right);
    }
    if (WindowManager::shared().keyWasPressed(Key::a)) {
        _terrain.shiftCursor(Direction::left);
    }
    if (WindowManager::shared().keyWasPressed(Key::w)) {
        _terrain.shiftCursor(Direction::up);
    }
    if (WindowManager::shared().keyWasPressed(Key::s)) {
        _terrain.shiftCursor(Direction::down);
    }

    if (WindowManager::shared().keyWasPressed(Key::enter)) {
        _terrain.shiftToCursor();
    }
}
