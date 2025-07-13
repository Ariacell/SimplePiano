#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>


namespace debugUI
{
    struct Window {
        glm::vec2 location;
        glm::vec2 size;
    };
    
    struct DebugLayerMainWindowData
    {
        bool isWireframeRenderingEnabled;
        DebugLayerMainWindowData() {
            isWireframeRenderingEnabled = false;
        }
    };
}

class DebugUiLayer
{
public:
    void init(GLFWwindow *window, debugUI::DebugLayerMainWindowData *debugWindowData);
    void beginFrame();
    void endFrame();
    void shutdown();

    /// @brief Render the main debug window for the application
    /// @param window
    void renderDebugWindow(GLFWwindow *window, debugUI::DebugLayerMainWindowData *debugWindowData);

    /// @brief Should usually be only called when the debug layer is being rendered, draws a crosshair to the centre of the window
    /// @param window
    void drawDot(double x, double y);

    /// @brief Find whether debug wireframe drawing is requested
    /// @return isWireframeDrawingEnabled
    bool getIsWireframeDrawingEnabled();

private:
    debugUI::DebugLayerMainWindowData *debugWindowData;

    void makeDebugWindowMenu(debugUI::DebugLayerMainWindowData *debugWindowData);
    void makeGraphicsMenu(debugUI::DebugLayerMainWindowData *debugWindowData);
    void setWireframeMode(bool shouldUseWireframeMode);
};