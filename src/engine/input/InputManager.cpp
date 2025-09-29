#include <GLFW/glfw3.h>
#include <engine/input/InputKeys.h>
#include <engine/input/InputManager.h>

namespace Input {
InputManager::InputManager(Engine::IWindow &window) {
    // This pattern doesn't explicitly support separate inputs per window yet,
    // probably very busted if trying to split input
    window.SetKeyCallback([this](int key, int action, int mods) {
        this->keyCallback(key, action, mods);
    });
    window.SetCursorPosCallback(
        [this](double xpos, double ypos) { this->mouse_callback(xpos, ypos); });
    auto windowSize = window.GetWindowSize();
    lastMousePosition = glm::vec2(windowSize.x / 2, windowSize.y / 2);
}

void InputManager::keyCallback(int key, int action, int mods) {
    // Depending on the type of window it would be good to abstract away the
    // GLFW specific keypresses a bit more elegantly For now I map specific keys
    // to the application layer
    auto internalKeyId = AppKeyFromGlfwKey(key);
    auto internalKeyAction = AppKeyActionFromGlfwAction(action);
    if (internalKeyId == APP_KEY_F1 && action == APP_KEY_PRESS) {
        debugWindowVisible = !debugWindowVisible;
    }
    if (internalKeyId == APP_KEY_W && action == APP_KEY_PRESS &&
        (mods & GLFW_MOD_CONTROL)) {
        this->assertDebugSettingsBoundToInputManager();
        this->debugSettings->isWireframeRenderingEnabled =
            !this->debugSettings->isWireframeRenderingEnabled;
    }

    // Transitioning to a decoupled input state structure that can be fed into
    // my other components as needed to avoid spaghetti here
    if (action == APP_KEY_PRESS) {
        inputState.PressKey(internalKeyId);
    } else if (action == APP_KEY_RELEASE) {
        inputState.ReleaseKey(internalKeyId);
    }
}

void InputManager::mouse_callback(double xpos, double ypos) {
    static double lastX = xpos, lastY = ypos;
    inputState.SetMouseDelta(static_cast<float>(xpos - lastX),
                             static_cast<float>(lastY - ypos));
    lastX = xpos;
    lastY = ypos;
}

void InputManager::scroll_callback(double xoffset, double yoffset) {
    // Todo, store scroll inputs
}

unsigned int InputManager::bindDebugSettings(
    Debug::DebugLayerMainWindowData *debugData) {
    this->debugSettings = debugData;
    return 0;
}

bool InputManager::isDebugWindowVisible() const {
    return debugWindowVisible;
}

void InputManager::assertDebugSettingsBoundToInputManager() {
    assert(this->debugSettings != NULL &&
           "No debug settings found bound to the InputManager, did you perhaps "
           "forget to call bindDebugSettings() after creating the input "
           "manager and debugUI?");
}
}  // namespace Input