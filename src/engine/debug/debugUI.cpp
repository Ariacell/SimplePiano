#include "debugUI.h"

#include <appstate.h>
#include <components/camera/Camera.h>
#include <engine/input/InputManager.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <implot.h>

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

void DebugUiLayer::init(GLFWwindow *window,
                        Debug::DebugLayerMainWindowData *debugWindowData,
                        Camera *camera) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    this->debugWindowData = debugWindowData;
    this->cameraToTrack = camera;
    // Initialise empty frame rate data times
    for (int i = 0; i < 60; ++i) {
        debugWindowData->frameTimeData.push_back(0.f);
    }
}

void DebugUiLayer::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugUiLayer::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        // Update and Render additional Platform Windows
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void DebugUiLayer::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void makeInputDataMenu(Input::InputState inputState) {
    if (ImGui::BeginListBox("Input CURRENT keys")) {
        for (auto key : inputState.GetCurrentKeys()) {
            if (!key.second) {
                continue;
            }
            ImGui::Text(std::to_string(key.first).c_str());
        }
        ImGui::EndListBox();
    }

    if (ImGui::BeginListBox("Input PRESSED keys")) {
        for (auto key : inputState.GetPressedKeys()) {
            ImGui::Text(std::to_string(key.first).c_str());
        }
        ImGui::EndListBox();
    }
}

void DebugUiLayer::renderDebugWindow(
    GLFWwindow *window, Debug::DebugLayerMainWindowData *debugWindowData,
    State::ApplicationState *appState, Input::InputManager *inputMgr) {
    IM_ASSERT(ImGui::GetCurrentContext() != NULL &&
              "Missing Dear ImGui context. Refer to examples app!");
    // const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    float deltaTime = ImGui::GetIO().DeltaTime;
    debugWindowData->frameTimeData.erase(
        debugWindowData->frameTimeData.begin());
    debugWindowData->frameTimeData.push_back(1 / deltaTime);

    // Optimisation possible here to confirm whether the debug main menu is
    // expanded, but not for today
    //  if(!ImGui::Begin("App Debugger", 0, ImGuiWindowFlags_MenuBar)) { return;
    //  }

    ImGui::Begin("App Debugger", 0, ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(500, 500), 0);
    // ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::Text("F1 toggled this debug window.");
    makeGraphicsMenu(this->debugWindowData);
    makeLocationDataMenu(this->cameraToTrack);
    makeInputDataMenu(inputMgr->GetInputState());
    makeDebugWindowMenu(this->debugWindowData);
    DebugUiLayer::drawDot(windowWidth / 2, windowHeight / 2);
    ImGui::End();
    ImGui::Begin("Utility Info");
    DebugUiLayer::drawUtilityGraphWidget(windowWidth, windowHeight, deltaTime);
    ImGui::End();
}

void DebugUiLayer::drawUtilityGraphWidget(int windowHeight, int windowWidth,
                                          float deltaTime) {
    // Todo: Dock this to the upper right corner and improve the styling
    if (ImPlot::BeginSubplots("Graphed Data", 1, 1,
                              ImVec2(windowWidth / 4, windowHeight / 4))) {
        if (ImPlot::BeginPlot("")) {
            ImPlot::SetupAxis(ImAxis_X1, "", ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxis(ImAxis_Y1, "Frame Rate", ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 5000);

            std::vector<float> x_axis_labels;
            for (int i = 0; i < 60; i++) {
                x_axis_labels.push_back(i);
            }
            ImPlot::PlotLine("Frame Rate", x_axis_labels.data(),
                             debugWindowData->frameTimeData.data(),
                             debugWindowData->frameTimeData.size());
            ImPlot::EndPlot();
        }
        ImPlot::EndSubplots();
    }
}

void DebugUiLayer::drawDot(double x, double y) {
    auto draw = ImGui::GetBackgroundDrawList();
    draw->AddCircle(ImVec2(x, y), 5, IM_COL32(255, 255, 255, 255), 100, 2.f);
}

bool DebugUiLayer::getIsWireframeDrawingEnabled() {
    return this->debugWindowData->isWireframeRenderingEnabled;
}

void DebugUiLayer::makeGraphicsMenu(
    Debug::DebugLayerMainWindowData *debugWindowData) {
    if (ImGui::BeginMenu("Graphics")) {
        ImGui::Checkbox("Wireframe Rendering",
                        &debugWindowData->isWireframeRenderingEnabled);
        ImGui::EndMenu();
    }
}

void DebugUiLayer::makeLocationDataMenu(Camera *trackedCamera) {
    if (ImGui::BeginMenu("Location Info")) {
        if (ImGui::BeginTable("Camera Details", 2)) {
            ImGui::TableSetupColumn("Entry",
                                    ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Value",
                                    ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();

            ImGui::TableNextRow();
            auto cameraPosX = std::to_string(trackedCamera->Position.x);
            auto cameraPosY = std::to_string(trackedCamera->Position.y);
            auto cameraPosZ = std::to_string(trackedCamera->Position.z);
            ImGui::TableSetColumnIndex(0);
            ImGui::InputText("CameraPosition X", &cameraPosX);
            ImGui::TableSetColumnIndex(0);
            ImGui::InputText("CameraPosition Y", &cameraPosY);
            ImGui::TableSetColumnIndex(0);
            ImGui::InputText("CameraPosition Z", &cameraPosZ);
            ImGui::EndTable();
        }

        ImGui::EndMenu();
    }
}

void DebugUiLayer::makeDebugWindowMenu(
    Debug::DebugLayerMainWindowData *debugWindowData) {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {
                ImGui::OpenPopup("FilePopup");

                if (ImGui::BeginPopup("FilePopup")) {
                    ImGui::Button("Test");
                    ImGui::EndPopup();
                }
            }

            if (ImGui::MenuItem("Load...")) {
            }
            if (ImGui::MenuItem("Save...")) {
            }
            if (ImGui::MenuItem("Save As...")) {
            }
            if (ImGui::MenuItem("Exit")) {
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void DebugUiLayer::setWireframeMode(bool shouldUseWireframeMode) {
    DebugUiLayer::debugWindowData->isWireframeRenderingEnabled =
        shouldUseWireframeMode;
}
