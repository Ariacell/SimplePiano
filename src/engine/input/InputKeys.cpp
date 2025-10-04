#include <engine/input/InputKeys.h>

namespace Input {

AppKeyAction AppKeyActionFromGlfwAction(int glfwKeyAction) {
    switch (glfwKeyAction) {
        case GLFW_RELEASE:
            return APP_KEY_RELEASE;
        case GLFW_PRESS:
            return APP_KEY_PRESS;
        default:
            return APP_KEY_UNKNOWN_ACTION;
    }
}

AppKey AppKeyFromGlfwKey(int glfwKey) {
    using namespace Input;
    switch (glfwKey) {
        case GLFW_KEY_F1:
            return AppKey::APP_KEY_F1;
        case GLFW_KEY_F2:
            return AppKey::APP_KEY_F2;
        case GLFW_KEY_F3:
            return AppKey::APP_KEY_F3;
        case GLFW_KEY_F4:
            return AppKey::APP_KEY_F4;

        case GLFW_MOUSE_BUTTON_1:
            return AppKey::APP_KEY_MOUSE_1;
        case GLFW_MOUSE_BUTTON_2:
            return AppKey::APP_KEY_MOUSE_2;

        case GLFW_KEY_SPACE:
            return AppKey::APP_KEY_SPACE;
        case GLFW_KEY_LEFT_CONTROL:
            return APP_KEY_LCTRL;
        case GLFW_KEY_ESCAPE:
            return APP_KEY_ESCAPE;

        case GLFW_KEY_Q:
            return AppKey::APP_KEY_Q;
        case GLFW_KEY_E:
            return AppKey::APP_KEY_E;
        case GLFW_KEY_W:
            return AppKey::APP_KEY_W;
        case GLFW_KEY_R:
            return AppKey::APP_KEY_R;
        case GLFW_KEY_A:
            return AppKey::APP_KEY_A;
        case GLFW_KEY_S:
            return AppKey::APP_KEY_S;
        case GLFW_KEY_D:
            return AppKey::APP_KEY_D;
        default:
            return AppKey::APP_KEY_UNMAPPED;
    }
}
}  // namespace Input