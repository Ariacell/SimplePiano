#include "input.h"
#include <GLFW/glfw3.h>
#include <ui/debugUI.h>

namespace Input
{
    void InputManager::keyCallback(int key, int action, int mods)
    {
        if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        {
            debugWindowVisible = !debugWindowVisible;
        }
        if (key == GLFW_KEY_W && (mods & GLFW_MOD_CONTROL)) {
            this->assertDebugSettingsBoundToInputManager();
            this->debugSettings->isWireframeRenderingEnabled = !this->debugSettings->isWireframeRenderingEnabled;
        }
    }

    unsigned int InputManager::bindDebugSettings(debugUI::DebugLayerMainWindowData *debugData) {
        this->debugSettings = debugData;
        return 0;
    }

    bool InputManager::isDebugWindowVisible() const
    {
        return debugWindowVisible;
    }

    void InputManager::assertDebugSettingsBoundToInputManager() {
        assert(this->debugSettings != NULL && "No debug settings found bound to the InputManager, did you perhaps forget to call bindDebugSettings() after creating the input manager and debugUI?");
    }
}