#pragma once
#include <unordered_map>

namespace Input {

class InputState {
public:
    void PressKey(int key);
    void ReleaseKey(int key);
    bool IsKeyDown(int key) const;
    bool WasKeyPressed(int key) const;

    /// @brief Should be called once per game loop frame after all reliant code
    /// has executed to clear pressed keys and mouse delta
    void EndFrame();

    // Mouse input
    void SetMouseDelta(float dx, float dy);
    void GetMouseDelta(float &dx, float &dy) const;

    std::unordered_map<int, bool> GetCurrentKeys();
    std::unordered_map<int, bool> GetPressedKeys();

private:
    std::unordered_map<int, bool> currentKeys;
    std::unordered_map<int, bool> pressedKeys;

    float mouseDeltaX = 0.0f;
    float mouseDeltaY = 0.0f;
};

}  // namespace Input