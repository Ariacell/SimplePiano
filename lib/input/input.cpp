#include "input.h"
#include <GLFW/glfw3.h>

namespace Input
{
    void InputManager::keyCallback(int key, int action)
    {
        if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        {
            debugWindowVisible = !debugWindowVisible;
        }
    }

    bool InputManager::isDebugWindowVisible() const
    {
        return debugWindowVisible;
    }
}