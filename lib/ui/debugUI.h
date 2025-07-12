#pragma once

#include <GLFW/glfw3.h>

class DebugUiLayer
{
public:
    void init(GLFWwindow *window);
    void beginFrame();
    void endFrame();
    void shutdown();

    /// @brief Render the main debug window for the application
    /// @param window 
    void renderDebugWindow(GLFWwindow *window);

    /// @brief Should usually be only called when the debug layer is being rendered, draws a crosshair to the centre of the window
    /// @param window
    void drawCentreCrosshair(GLFWwindow *window);
};