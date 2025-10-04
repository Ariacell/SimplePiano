#pragma once
#include <GLFW/glfw3.h>

namespace Input {
enum KeyBindNames {
    CAMERA_FORWARD,
    CAMERA_BACK,
    CAMERA_RIGHT,
    CAMERA_LEFT,
    CAMERA_UP,
    CAMERA_ROLL_RIGHT,
    CAMERA_ROLL_LEFT,
};

// Not sure if I want to bother with a better macro style to map input keys,
// need some more experience with window managers besides GLFW
enum AppKey {

    APP_KEY_F1,
    APP_KEY_F2,
    APP_KEY_F3,
    APP_KEY_F4,
    APP_KEY_F5,

    APP_KEY_MOUSE_1,
    APP_KEY_MOUSE_2,
    APP_KEY_MOUSE_SCROLL_Y,

    APP_KEY_SPACE,
    APP_KEY_LCTRL,
    APP_KEY_ESCAPE,

    APP_KEY_Q,
    APP_KEY_W,
    APP_KEY_E,
    APP_KEY_A,
    APP_KEY_S,
    APP_KEY_D,

    APP_KEY_UNMAPPED = -1
};

enum AppKeyAction {
    APP_KEY_RELEASE = 0,
    APP_KEY_PRESS = 1,
    APP_KEY_UNKNOWN_ACTION = -1
};

AppKeyAction AppKeyActionFromGlfwAction(int glfwKeyAction);

AppKey AppKeyFromGlfwKey(int glfwKey);
}  // namespace Input