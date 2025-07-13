#pragma once
#include <ui/debugUI.h>
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
        debugUI::DebugLayerMainWindowData *debugSettings;
        void assertDebugSettingsBoundToInputManager();
        bool debugWindowVisible = false;
        
    };
}