#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <components/camera/Camera.h>
#include <engine/application/ApplicationState.h>
#include <engine/debug/DebugState.h>
#include <engine/input/InputManager.h>

#include <glm/vec2.hpp>
#include <vector>

namespace PianoCore {
struct Window {
    glm::vec2 location;
    glm::vec2 size;
};

class DebugUi {
public:
    void init(GLFWwindow *window,
              Debug::DebugLayerMainWindowData *debugWindowData,
              Input::InputManager &inputMgr, PerspectiveCamera *camera);
    void beginFrame();
    void endFrame();
    void shutdown();

    GLFWwindow &GetMainWindow();
    Debug::DebugLayerMainWindowData &GetDebugWindowData();
    Input::InputManager &GetInputManagerRef();

    /// @brief Render the main debug window for the application
    /// @param window
    void renderDebugWindow(GLFWwindow *window,
                           Debug::DebugLayerMainWindowData *debugWindowData);

    /// @brief Should usually be only called when the debug layer is being
    /// rendered, draws a crosshair to the centre of the window
    /// @param window
    void drawDot(double x, double y);

    /// @brief Find whether debug wireframe drawing is requested
    /// @return isWireframeDrawingEnabled
    bool getIsWireframeDrawingEnabled();

private:
    GLFWwindow *mainWindow;
    Input::InputManager *inputManagerReference;
    Debug::DebugLayerMainWindowData *debugWindowData;
    PerspectiveCamera *cameraToTrack;

    void drawUtilityGraphWidget(int windowHeight, int windowWidth,
                                float deltaTime);
    void makeDebugWindowMenu(Debug::DebugLayerMainWindowData *debugWindowData);
    void makeLocationDataMenu(PerspectiveCamera *trackedCamera);
    void makeGraphicsMenu(Debug::DebugLayerMainWindowData *debugWindowData);
    void setWireframeMode(bool shouldUseWireframeMode);
};
}  // namespace PianoCore