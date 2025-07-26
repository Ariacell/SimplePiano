#pragma once
#include <chrono>
#include <components/camera/Camera.h>
#include <GLFW/glfw3.h>
#include <engine/input/InputState.h>
#include <engine/debug/DebugState.h>
#include <engine/IWindow.h>

namespace Input
{
    class InputManager
    {
    public:
        InputManager(Engine::IWindow *window, Camera *camera);
        void keyCallback(int key, int action, int mods);
        void mouse_callback(double xpos, double ypos);
        void scroll_callback(double xoffset, double yoffset);

        Camera *bindNewCamera(Camera *cameraToBind);

        bool isDebugWindowVisible() const;

        unsigned int bindDebugSettings(Debug::DebugLayerMainWindowData *debugSettings);

        InputState GetInputState() { return this->inputState; };

        // End a frame for input purposes (clears frame based data such as key presses and mouse deltas)
        void EndFrame()
        {
            this->inputState.EndFrame();
        };

    private:
        // Will be used to stop inputs going wacko mode, should be config but here for now.
        std::chrono::milliseconds inputRateLimiter = std::chrono::milliseconds(10);

        Debug::DebugLayerMainWindowData *debugSettings;
        void assertDebugSettingsBoundToInputManager();
        bool debugWindowVisible = false;

        // Input State internal so it can only be manipulated by the manager
        Input::InputState inputState;

        // Camera this input manager is currently bound to control
        Camera *currentCamera;

        // Mouse input variables
        glm::vec2 lastMousePosition;
    };
}