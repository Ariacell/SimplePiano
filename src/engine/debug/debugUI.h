#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec2.hpp>
#include <components/camera/Camera.h>
#include <appstate.h>
#include <engine/input/InputManager.h>
#include <engine/debug/DebugState.h>

namespace debugUI
{
    struct Window
    {
        glm::vec2 location;
        glm::vec2 size;
    };
}

class DebugUiLayer
{
public:
    void init(GLFWwindow *window, Debug::DebugLayerMainWindowData *debugWindowData, Camera *camera);
    void beginFrame();
    void endFrame();
    void shutdown();

    /// @brief Render the main debug window for the application
    /// @param window
    void renderDebugWindow(GLFWwindow *window, Debug::DebugLayerMainWindowData *debugWindowData, State::ApplicationState *appState, Input::InputManager *inputMgr);

    /// @brief Should usually be only called when the debug layer is being rendered, draws a crosshair to the centre of the window
    /// @param window
    void drawDot(double x, double y);

    /// @brief Find whether debug wireframe drawing is requested
    /// @return isWireframeDrawingEnabled
    bool getIsWireframeDrawingEnabled();

private:
    Debug::DebugLayerMainWindowData *debugWindowData;
    Camera *cameraToTrack;

    void drawUtilityGraphWidget(int windowHeight, int windowWidth, float deltaTime);
    void makeDebugWindowMenu(Debug::DebugLayerMainWindowData *debugWindowData);
    void makeLocationDataMenu(Camera *trackedCamera);
    void makeGraphicsMenu(Debug::DebugLayerMainWindowData *debugWindowData);
    void setWireframeMode(bool shouldUseWireframeMode);
};