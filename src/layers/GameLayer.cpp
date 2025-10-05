#define GLFW_INCLUDE_NONE
#include <engine/IRenderer.h>
#include <engine/core/log.h>
#include <engine/graphics/OpenGLLine.h>
#include <engine/input/InputKeys.h>
#include <engine/physics/Raycasting.h>
#include <game/components/BoundingBoxComponent.h>
#include <game/components/Material.h>
#include <game/components/Model.h>
#include <game/components/SelectableComponent.h>
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
    openGlShader = std::make_shared<Shaders::OpenGlShader>(
        "./shaders/base.vert", "./shaders/base.frag");
    std::shared_ptr<Component::Material> cloudMat(
        new Component::Material(openGlShader, "path"));

    Ref<Component::Model> ourModel =
        std::make_shared<Component::Model>("models/backpack/backpack.obj");
    std::shared_ptr<Component::Model> cubeOpenGlModel(
        new Component::Model(Component::MeshType::Cube));

    std::shared_ptr<Component::Model> quadOpenGlModel(
        new Component::Model(Component::MeshType::Quad));

    cloudObj.AddComponent<Component::ModelComponent>(ourModel, openGlShader);
    cloudObj.AddComponent<Component::SelectableComponent>();

    cloudQuadObj.AddComponent<Component::ModelComponent>(quadOpenGlModel,
                                                         openGlShader);
    cloudQuadObj.AddComponent<Component::SelectableComponent>();
    cloudQuadObj.AddComponent<Component::BoundingBoxComponent>(
        *quadOpenGlModel);
}

void PianoAppGameLayer::Init() {
    PianoCore::Log::Info("Begin init Game Layer");
    simulationTimer.Init();

    PianoCore::Log::Info("Finished init Game Layer");
}

void PianoAppGameLayer::Update(Input::InputManager &input) {
    simulationTimer.Update();

    simulationTimer.TickTimer(
        [&]() {
            // blah
            // Do physics/app state things
            // cloudObj.GetTransform()->translate(glm::vec3(.05F, .0F, .0F));
            cloudObj.GetTransform()->rotate(
                glm::quat(glm::highp_vec3(.0F, .0F, .05F)));
        },
        5);
    if (input.GetInputState().WasKeyPressed(Input::APP_KEY_R) &&
        input.GetInputState().IsKeyDown(Input::APP_KEY_LCTRL)) {
        // Reload shader
        PianoCore::Log::Info("Reloading shader!");
        openGlShader->reload();
    }

    // Object selection
    if (input.GetInputState().WasKeyPressed(Input::APP_KEY_MOUSE_1)) {
        glm::vec2 windowSize = parentApplication.GetApplicationState()
                                   ->mainWindow->GetWindowSize();
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0F), (float)windowSize.x / (float)windowSize.y,
            0.1F, 100.0F);
        glm::vec3 worldPos = glm::unProject(
            glm::vec3(input.GetMousePosition().x,
                      windowSize.y - input.GetMousePosition().y, 0.0),
            mainCamera.GetViewMatrix(), projection,
            glm::vec4(0, 0, windowSize.x, windowSize.y));
        glm::vec3 rayMouse = glm::normalize(worldPos - mainCamera.Position);
        std::string logMsg = std::format(
            "Checking for collisions with the bounding quad along "
            "vector: %s, %s, %s, starting from camera position %s, %s, %s",
            rayMouse.x, rayMouse.y, rayMouse.z, mainCamera.Position.x,
            mainCamera.Position.y, mainCamera.Position.z);
        // PianoCore::Log::Info(logMsg);
        float hitDistance = 0.0F;
        PianoPhysics::Ray ray(mainCamera.Position, rayMouse);
        if (PianoPhysics::CheckRayToAABBIntersection(
                ray,
                cloudQuadObj.GetComponent<Component::BoundingBoxComponent>()
                    ->GetMinExtents(),
                cloudQuadObj.GetComponent<Component::BoundingBoxComponent>()
                    ->GetMaxExtents(),
                hitDistance)) {
            PianoCore::Log::Info("INTERSECTION!");
            cloudQuadObj.GetComponent<Component::SelectableComponent>()
                ->SetSelected(true);
        } else {
            cloudQuadObj.GetComponent<Component::SelectableComponent>()
                ->SetSelected(false);
        }
    }

    mainCamera.ProcessInput(input.GetInputState(),
                            parentApplication.GetApplicationState()
                                ->framerateTimer.GetTickSizeSeconds());
}

void PianoAppGameLayer::Render() {
    Engine::IWindow &window =
        *parentApplication.GetApplicationState()->mainWindow;

    auto current_window_size = window.GetWindowSize();

    glm::mat4 view = glm::mat4(1.0F);
    view = mainCamera.GetViewMatrix();
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
    unsigned int selectedLoc =
        glGetUniformLocation(openGlShader->GetID(), "isSelected");
    glUniform1i(
        selectedLoc,
        cloudObj.GetComponent<Component::SelectableComponent>()->IsSelected()
            ? 1
            : 0);
    renderer.DrawObject(&cloudObj);
    glUniform1i(selectedLoc,
                cloudQuadObj.GetComponent<Component::SelectableComponent>()
                        ->IsSelected()
                    ? 1
                    : 0);
    renderer.DrawObject(&cloudQuadObj);

    // Debug line to draw the bounding box 
    auto bb = cloudQuadObj.GetComponent<Component::BoundingBoxComponent>();
    auto line = Line(bb->GetMinExtents(), bb->GetMaxExtents());
    line.setMVP(projection * view);
    line.draw();

}
void PianoAppGameLayer::Suspend() {
    PianoCore::Log::Info("Suspending PianoAppGameLayer");
}

PianoAppGameLayer::~PianoAppGameLayer() {
    PianoCore::Log::Info("Calling Destructor for PianoAppGameLayer");
}
}  // namespace PianoApp
