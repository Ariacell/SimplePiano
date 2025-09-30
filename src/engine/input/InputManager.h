#pragma once

#include <components/camera/Camera.h>
#include <engine/IWindow.h>
#include <engine/core/pointer.h>
#include <engine/debug/DebugState.h>
#include <engine/input/InputState.h>

#include <chrono>

namespace Input {
class InputManager {
public:
    InputManager(Engine::IWindow &window);
    void keyCallback(int key, int action, int mods);
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);

    bool isDebugWindowVisible() const;

    unsigned int bindDebugSettings(Debug::DebugLayerMainWindowData *debugData);

    InputState GetInputState() {
        return this->inputState;
    };

    glm::vec2 GetMousePosition() {
        return lastMousePosition;
    }

    // End a frame for input purposes (clears frame based data such as key
    // presses and mouse deltas)
    void EndFrame() {
        this->inputState.EndFrame();
    };

private:
    // Will be used to stop inputs going wacko mode, should be config but here
    // for now.
    std::chrono::milliseconds inputRateLimiter = std::chrono::milliseconds(10);

    Debug::DebugLayerMainWindowData *debugSettings;
    void assertDebugSettingsBoundToInputManager();
    bool debugWindowVisible = false;

    // Input State internal so it can only be manipulated by the manager
    Input::InputState inputState;

    // Mouse input variables
    glm::vec2 lastMousePosition;
};
}  // namespace Input