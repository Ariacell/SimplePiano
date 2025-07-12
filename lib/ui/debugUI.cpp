#include "debugUI.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

struct DebugLayerMainWindowData {
    
};

void DebugUiLayer::init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        // Update and Render additional Platform Windows
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void DebugUiLayer::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DebugUiLayer::renderDebugWindow(GLFWwindow *window)
{
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");
    static DebugLayerMainWindowData debugWindowData;
    // const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    //Optimisation possible here to confirm whether the debug main menu is expanded, but not for today
    // if(!ImGui::Begin("App Debugger", 0, ImGuiWindowFlags_MenuBar)) { return; }
    
    ImGui::Begin("App Debugger", 0, ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(200, 200), 0);
    // ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::Text("F1 toggled this debug window.");
    makeDebugWindowMenu();
    DebugUiLayer::drawDot(windowWidth/2, windowHeight/2);
    ImGui::End();
}

void DebugUiLayer::drawDot(double x, double y)
{
    auto draw = ImGui::GetBackgroundDrawList();
    draw->AddCircle(ImVec2(x, y), 5, IM_COL32(255, 255, 255, 255), 100, 2.f);
}

void DebugUiLayer::makeDebugWindowMenu() {
    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New"))
            {
                ImGui::OpenPopup("FilePopup");

                if (ImGui::BeginPopup("FilePopup"))
                {
                    ImGui::Button("Test");
                    ImGui::EndPopup();
                }
            }

            if(ImGui::MenuItem("Load...")) {}
            if(ImGui::MenuItem("Save...")) {}
            if(ImGui::MenuItem("Save As...")) {}
            if(ImGui::MenuItem("Exit")) {}

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

}