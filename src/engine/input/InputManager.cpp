#include <engine/input/InputManager.h>
#include <GLFW/glfw3.h>

namespace Input
{
    InputManager::InputManager(GLFWwindow *window, Camera *camera)
    {
        // This assumes a separate input manager per window, need to decouple this from glfw still
        glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        lastMousePosition = glm::vec2(windowWidth / 2, windowHeight / 2);
        currentCamera = camera;
    }

    void InputManager::keyCallback(int key, int action, int mods)
    {
        if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        {
            debugWindowVisible = !debugWindowVisible;
        }
        if (key == GLFW_KEY_W && action == GLFW_PRESS && (mods & GLFW_MOD_CONTROL))
        {
            this->assertDebugSettingsBoundToInputManager();
            this->debugSettings->isWireframeRenderingEnabled = !this->debugSettings->isWireframeRenderingEnabled;
        }

        // Transitioning to a decoupled input state structure that can be fed into my other components as needed to avoid spaghetti here
        if (action == GLFW_PRESS)
        {
            inputState.PressKey(key);
        }
        else if (action == GLFW_RELEASE)
        {
            inputState.ReleaseKey(key);
        }
    }

    void InputManager::mouse_callback(double xpos, double ypos)
    {
        static double lastX = xpos, lastY = ypos;
        inputState.SetMouseDelta(static_cast<float>(xpos - lastX), static_cast<float>(lastY - ypos));
        lastX = xpos;
        lastY = ypos;
    }

    void InputManager::scroll_callback(double xoffset, double yoffset)
    {
        // Todo, store scroll inputs
    }

    Camera *InputManager::bindNewCamera(Camera *cameraToBind)
    {
        // This shouldn't be necessary once the decoupled input state is being pased around the app update loop
        currentCamera = cameraToBind;
        return currentCamera;
    }

    unsigned int InputManager::bindDebugSettings(Debug::DebugLayerMainWindowData *debugData)
    {
        this->debugSettings = debugData;
        return 0;
    }

    bool InputManager::isDebugWindowVisible() const
    {
        return debugWindowVisible;
    }

    void InputManager::assertDebugSettingsBoundToInputManager()
    {
        assert(this->debugSettings != NULL && "No debug settings found bound to the InputManager, did you perhaps forget to call bindDebugSettings() after creating the input manager and debugUI?");
    }
}