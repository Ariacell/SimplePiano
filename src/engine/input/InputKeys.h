#pragma once
#include <GLFW/glfw3.h>

namespace Input {
    enum KeyBindNames
    {
        CAMERA_FORWARD,
        CAMERA_BACK,
        CAMERA_RIGHT,
        CAMERA_LEFT,
    };

    enum AppKey {
        APP_KEY_F1,
        APP_KEY_W,
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
}