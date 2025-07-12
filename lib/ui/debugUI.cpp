#include "debugUI.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

void DebugUiLayer::init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void DebugUiLayer::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugUiLayer::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugUiLayer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DebugUiLayer::renderDebugWindow(GLFWwindow *window)
{
    ImGui::Begin("Debug Window");
    ImGui::SetWindowSize(ImVec2(200, 200), 0);
    ImGui::SetWindowPos(ImVec2(0, 0));
    
    ImGui::Text("F1 toggled this debug window.");
    ImGui::End();
}

void DebugUiLayer::drawCentreCrosshair(GLFWwindow *window) {
    auto draw = ImGui::GetBackgroundDrawList();
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    draw->AddCircle(ImVec2(windowWidth/2, windowHeight/2), 5, IM_COL32(255, 255, 255, 255), 100, 2.f);
}