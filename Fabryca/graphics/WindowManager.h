#pragma once

#include "Foundation.h"
#include "graphics/glad.h"

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

using Window = GLFWwindow;


enum class Key;
enum class KeyState;


class WindowManager final {
public:
    static WindowManager& shared();

    Void initWindow(const Size& size, const std::string& title);

    Size windowSize() const;
    Int windowWidth() const;
    Int windowHeight() const;
    Float windowAspectRatio() const;

    Void setMinimumWindowSize(const Size& size) const;
    Void setWindowSize(const Size& size) const;

    Void registerWindowSizeCallback(const std::function<Void (Int, Int)>& callback);

    KeyState keyState(Key key);
    Bool keyWasPressed(Key key);

    Bool windowShouldClose() const;
    Void swapBuffers() const;
    Void pollEvents() const;

    Void terminate() const;

private:
    static WindowManager* _shared;
    
    Window* _window;
    std::vector<KeyState> _previousKeyState;
    std::vector<std::function<Void (Int, Int)>> _windowSizeCallbacks;


    WindowManager();
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator= (const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;
    WindowManager& operator= (WindowManager&&) = delete;
    ~WindowManager();


    static Void _windowSizeDidChange(Window* window, Int width, Int height);
};


enum class Key {
    space = GLFW_KEY_SPACE,
    zero = GLFW_KEY_0,
    one = GLFW_KEY_1,
    two = GLFW_KEY_2,
    three = GLFW_KEY_3,
    four = GLFW_KEY_4,
    five = GLFW_KEY_5,
    six = GLFW_KEY_6,
    seven = GLFW_KEY_7,
    eight = GLFW_KEY_8,
    nine = GLFW_KEY_9,
    a = GLFW_KEY_A,
    b = GLFW_KEY_B,
    c = GLFW_KEY_C,
    d = GLFW_KEY_D,
    e = GLFW_KEY_E,
    f = GLFW_KEY_F,
    g = GLFW_KEY_G,
    h = GLFW_KEY_H,
    i = GLFW_KEY_I,
    j = GLFW_KEY_J,
    k = GLFW_KEY_K,
    l = GLFW_KEY_L,
    m = GLFW_KEY_M,
    n = GLFW_KEY_N,
    o = GLFW_KEY_O,
    p = GLFW_KEY_P,
    q = GLFW_KEY_Q,
    r = GLFW_KEY_R,
    s = GLFW_KEY_S,
    t = GLFW_KEY_T,
    u = GLFW_KEY_U,
    v = GLFW_KEY_V,
    w = GLFW_KEY_W,
    x = GLFW_KEY_X,
    y = GLFW_KEY_Y,
    z = GLFW_KEY_Z,
    escape = GLFW_KEY_ESCAPE,
    enter = GLFW_KEY_ENTER,
    right = GLFW_KEY_RIGHT,
    left = GLFW_KEY_LEFT,
    down = GLFW_KEY_DOWN,
    up = GLFW_KEY_UP
};


enum class KeyState {
    released = GLFW_RELEASE,
    pressed = GLFW_PRESS
};
