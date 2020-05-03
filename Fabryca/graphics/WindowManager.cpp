#include "WindowManager.h"
#include "Renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>


WindowManager* WindowManager::_shared = nullptr;

WindowManager& WindowManager::shared() {
    if (!_shared) {
        _shared = new WindowManager();
    }

    return *_shared;
}

WindowManager::WindowManager():
    _window(nullptr),
    _previousKeyState(std::vector<KeyState>(350, KeyState::released)),
    _windowSizeCallbacks()
{
    if (!glfwInit()) {
        terminate();
        throw std::runtime_error("Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);
}

WindowManager::~WindowManager() {
    terminate();
}

Void WindowManager::initWindow(const Size& size, const std::string& title) {
    if (_window) {
        terminate();
        throw std::runtime_error("Window already exists.");
    }

    _window = glfwCreateWindow(size.width, size.height, title.c_str(), nullptr, nullptr);

    if (!_window) {
        terminate();
        throw std::runtime_error("Failed to create window.");
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        terminate();
        throw std::runtime_error("Failed to load OpenGL.");
    }

    glfwSetWindowSizeCallback(_window, _windowSizeDidChange);
}

Size WindowManager::windowSize() const {
    Size size;
    glfwGetWindowSize(_window, &size.width, &size.height);

    return size;
}

Int WindowManager::windowWidth() const {
    return windowSize().width;
}

Int WindowManager::windowHeight() const {
    return windowSize().height;
}

Float WindowManager::windowAspectRatio() const {
    auto [width, height] = windowSize();

    return static_cast<Float>(width) / height;
}

Void WindowManager::setMinimumWindowSize(const Size& size) const {
    glfwSetWindowSizeLimits(_window, size.width, size.height, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

Void WindowManager::setWindowSize(const Size& size) const {
    glfwSetWindowSize(_window, size.width, size.height);
}

Void WindowManager::registerWindowSizeCallback(const std::function<Void (Int, Int)>& callback) {
    _windowSizeCallbacks.push_back(callback);
    auto [width, height] = WindowManager::shared().windowSize();
    callback(width, height);
}

KeyState WindowManager::keyState(Key key) {
    KeyState state = static_cast<KeyState>(glfwGetKey(_window, static_cast<Int>(key)));
    _previousKeyState[static_cast<Int>(key)] = state;

    return state;
}

Bool WindowManager::keyWasPressed(Key key) {
    KeyState previousState = _previousKeyState[static_cast<Int>(key)];
    KeyState currentState = keyState(key);

    return previousState == KeyState::pressed && currentState == KeyState::released;
}

Bool WindowManager::windowShouldClose() const {
    return glfwWindowShouldClose(_window);
}

Void WindowManager::swapBuffers() const {
    glfwSwapBuffers(_window);
}

Void WindowManager::pollEvents() const {
    glfwPollEvents();
}

Void WindowManager::terminate() const {
    glfwTerminate();
}

Void WindowManager::_windowSizeDidChange(Window* window, Int width, Int height) {
    for (const std::function<Void (Int, Int)>& callback: _shared->_windowSizeCallbacks) {
        callback(width, height);
    }

    glfwSwapBuffers(window);
}
