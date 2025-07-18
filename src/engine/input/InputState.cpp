#include <engine/input/InputState.h>

void Input::InputState ::PressKey(int key) {
    if (!currentKeys[key]) {
        pressedKeys[key] = true;  // only true on the frame it's first pressed
    }
    currentKeys[key] = true;
}

void Input::InputState::ReleaseKey(int key) {
    currentKeys[key] = false;
}

bool Input::InputState::IsKeyDown(int key) const {
    auto it = currentKeys.find(key);
    return it != currentKeys.end() && it->second;
}

bool Input::InputState::WasKeyPressed(int key) const {
    auto it = pressedKeys.find(key);
    return it != pressedKeys.end() && it->second;
}

void Input::InputState::EndFrame() {
    pressedKeys.clear();
    mouseDeltaX = mouseDeltaY = 0.0f;
}

void Input::InputState::SetMouseDelta(float dx, float dy) {
    mouseDeltaX += dx;
    mouseDeltaY += dy;
}

void Input::InputState::GetMouseDelta(float& dx, float& dy) const {
    dx = mouseDeltaX;
    dy = mouseDeltaY;
}

std::unordered_map<int, bool> Input::InputState::GetCurrentKeys() {
    return this->currentKeys;
}

std::unordered_map<int, bool> Input::InputState::GetPressedKeys() {
    return this->pressedKeys;
}