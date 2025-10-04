#define GLFW_INCLUDE_NONE
#include <engine/IRenderer.h>
#include <engine/core/log.h>
#include <game/components/Material.h>
#include <game/components/Model.h>
#include <glad/glad.h>
#include <layers/GameLayer.h>

#include "engine/RendererFactory.h"
#include "engine/application/ApplicationConstants.h"
#include "game/components/ModelComponent.h"

namespace PianoApp {

PianoAppGameLayer::PianoAppGameLayer(PerspectiveCamera &mainGameCamera,
                                     PianoCore::Application &parentApp)
    : mainCamera(mainGameCamera),
      parentApplication(parentApp),
      renderer(*parentApp.GetRenderer()) {
    PianoCore::Log::Info("Constructing PianoAppGameLayer");
    simulationTimer = Util::Timer(
        PianoCore::APPLICATION_DEFAULTS::TARGET_SIMULATION_TICKS_PER_SECOND);
}

void PianoAppGameLayer::Init() {
    simulationTimer.Init();

#pragma region Temporary setup for scene geometry, to remove once Scene abstraction is ready
    openGlShader =
        std::make_shared<Shaders::OpenGlShader>("something", "something");
    std::shared_ptr<Component::Material> cloudMat(
        new Component::Material(openGlShader, "path"));

    Ref<Component::Model> ourModel =
        std::make_shared<Component::Model>("models/backpack/backpack.obj");
    std::shared_ptr<Component::Model> cubeOpenGlModel(
        new Component::Model(Component::MeshType::Cube));

    std::shared_ptr<Component::Model> quadOpenGlModel(
        new Component::Model(Component::MeshType::Quad));

    cloudObj.AddComponent<Component::ModelComponent>(ourModel, openGlShader);
    cloudQuadObj.AddComponent<Component::ModelComponent>(quadOpenGlModel,
                                                         openGlShader);
#pragma endregion
}

void PianoAppGameLayer::Update(Input::InputManager &input) {
    PianoCore::Log::Info("Update called for PianoAppGameLayer");
    simulationTimer.Update();

    simulationTimer.TickTimer(
        [&]() {
            // blah
            //  Do physics/app state things
            // std::cout << "Application Ticks so far: "
            //           << appStateTimer.GetTickCount() << std::endl;
            cloudObj.GetTransform()->translate(glm::vec3(.05F, .0F, .0F));
        },
        5);

    mainCamera.ProcessInput(input.GetInputState(),
                            parentApplication.GetApplicationState()
                                ->framerateTimer.GetTickSizeSeconds());
}

void PianoAppGameLayer::Render() {
    PianoCore::Log::Info("Render called for PianoAppGameLayer");

    Engine::IWindow &window =
        *parentApplication.GetApplicationState()->mainWindow;

#pragma region Rendering Logic

    auto current_window_size = window.GetWindowSize();

    glm::mat4 view = glm::mat4(1.0F);
    view = glm::lookAt(mainCamera.Position,
                       mainCamera.Position + mainCamera.Front, mainCamera.Up);
    glm::mat4 projection = glm::mat4(1.0F);
    projection = glm::perspective(
        glm::radians(45.0F),
        (float)current_window_size.x / (float)current_window_size.y, 0.1F,
        100.0F);

    // retrieve the matrix uniform locations and set up shaders
    openGlShader->use();
    unsigned int viewLoc = glGetUniformLocation(openGlShader->GetID(), "view");
    unsigned int projLoc =
        glGetUniformLocation(openGlShader->GetID(), "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

    renderer.DrawObject(&cloudObj);
    renderer.DrawObject(&cloudQuadObj);

    // // Playing with debug lines to start experimenting with raycasting
    // // to the quad
    // glm::vec2 windowSize =
    //     parentApplication.GetApplicationState()->mainWindow->GetWindowSize();
    // glm::vec3 worldPos = glm::unProject(
    //     glm::vec3(pianoApp->GetInput()->GetMousePosition().x,
    //               windowSize.y - pianoApp->GetInput()->GetMousePosition().y,
    //               0.0),
    //     view, projection, glm::vec4(0, 0, windowSize.x, windowSize.y));
    // glm::vec3 rayMouse = glm::normalize(worldPos - mainSceneCamera.Position);

    // auto line = Line(mainSceneCamera.Position, worldPos);
    // auto line2 = Line(worldPos, cloudQuadObj.GetTransform()->position);
    // line.setMVP(projection * view);
    // line.draw();
    // line2.setMVP(projection * view);
    // line2.draw();

    // PianoCore::Log::Info(std::format("Raycast to mouse: {0}, {1}, {2}",
    // rayMouse.x, rayMouse.y, rayMouse.z));

    // We don't present here anymore as there is now a single top level buffer
    // swap happening after all layers have written their content to the buffer.
    // renderer.Present();
#pragma endregion Rendering Logic
}
void PianoAppGameLayer::Suspend() {
    PianoCore::Log::Info("Suspending PianoAppGameLayer");
}
}  // namespace PianoApp
