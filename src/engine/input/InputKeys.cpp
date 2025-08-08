#include <engine/input/InputKeys.h>

namespace Input {
   
   AppKeyAction AppKeyActionFromGlfwAction(int glfwKeyAction) {
        switch(glfwKeyAction){
            case GLFW_RELEASE:
                return APP_KEY_RELEASE;
            case GLFW_PRESS:
                return APP_KEY_PRESS;
            default:
                return APP_KEY_UNKNOWN_ACTION;
        }
    }

    AppKey AppKeyFromGlfwKey(int glfwKey)
    {
        using namespace Input;
        switch (glfwKey)
        {
        case GLFW_KEY_F1:
            return AppKey::APP_KEY_F1;
        case GLFW_KEY_W:
            return AppKey::APP_KEY_W;
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
}