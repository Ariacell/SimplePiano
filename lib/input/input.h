#pragma once
#include <ui/debugUI.h>
#include <chrono>

namespace Input
{
    class InputManager
    {
    public:
        InputManager(GLFWwindow *window) {
            //This assumes a separate input manager per window, need to decouple this from glfw still
            glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
        }
        void keyCallback(int key, int action, int mods);
        bool isDebugWindowVisible() const;

        unsigned int bindDebugSettings(debugUI::DebugLayerMainWindowData *debugSettings);

    private:
        // Will be used to stop inputs going wacko mode, should be config but here for now.
        std::chrono::milliseconds inputRateLimiter = std::chrono::milliseconds(10);

        debugUI::DebugLayerMainWindowData *debugSettings;
        void assertDebugSettingsBoundToInputManager();
        bool debugWindowVisible = false;
        
    };
}