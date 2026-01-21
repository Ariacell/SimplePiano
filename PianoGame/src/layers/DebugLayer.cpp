#include "DebugLayer.h"

#include <input/InputKeys.h>

PianoApp::PianoAppDebugLayer::PianoAppDebugLayer(
    PerspectiveCamera &cameraToFollow,
    PianoCore::Application &parentApplication) {
    debugUi = std::make_unique<PianoCore::DebugUi>();

    GLFWwindow *glfwWindow = static_cast<GLFWwindow *>(
        parentApplication.GetApplicationState()->mainWindow->GetNativeHandle());
    debugUi->init(glfwWindow,
                  &parentApplication.GetApplicationState()
                       ->debugState.mainDebugWindowData,
                  *parentApplication.GetInput(), nullptr);
    parentApplication.GetInput()->bindDebugSettings(
        &parentApplication.GetApplicationState()
             ->debugState.mainDebugWindowData);
}

void PianoApp::PianoAppDebugLayer::Init() {
}

void PianoApp::PianoAppDebugLayer::Update(Input::InputManager &input) {
    if (input.GetInputState().WasKeyPressed(Input::APP_KEY_F1))
        m_isLayerVisible = !m_isLayerVisible;

    if (input.GetInputState().WasKeyPressed(Input::APP_KEY_W) &&
        input.GetInputState().WasKeyPressed(Input::APP_KEY_LCTRL)) {
        debugUi->GetDebugWindowData().isWireframeRenderingEnabled =
            !debugUi->GetDebugWindowData().isWireframeRenderingEnabled;
    }
}

void PianoApp::PianoAppDebugLayer::Render() {
    /* Render debug information last on top of the rest of the frame*/
    debugUi->beginFrame();

    if (m_isLayerVisible) {
        debugUi->renderDebugWindow(&debugUi->GetMainWindow(),
                                   &debugUi->GetDebugWindowData());
    }

    // renderer->SetWireframeRendering(
    //     m_AppState.debugState.mainDebugWindowData.isWireframeRenderingEnabled);
    // Note: While SP #7 is in play this call being here is causing the debug
    // windows to render behind the rest of the scene geometry. Should be fixed
    // once the rendering loop is properly extracted into application loop
    // callbacks.
    debugUi->endFrame();
}

void PianoApp::PianoAppDebugLayer::Suspend() {
}
