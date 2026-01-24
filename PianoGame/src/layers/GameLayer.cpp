#define GLFW_INCLUDE_NONE
#include <IRenderer.h>
#include <core/log.h>
#include <graphics/OpenGLLine.h>
#include <input/InputKeys.h>
#include <physics/Raycasting.h>
#include <components/BoundingBoxComponent.h>
#include <components/Material.h>
#include <components/Model.h>
#include <components/SelectableComponent.h>
#include <glad/glad.h>
#include <layers/GameLayer.h>

#include <RendererFactory.h>
#include <application/ApplicationConstants.h>
#include <components/ModelComponent.h>
#include <components/Transform.h>
#include "../components/Gravity.h"
#include "../components/Rigidbody.h"
#include "../components/Renderable.h"
#include <random>
#include <systems/RenderSystem.h>


extern World gWorld;

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

    gWorld.Init();
    
	// gWorld.RegisterComponent<Component::SelectableComponent>();
	// gWorld.RegisterComponent<Component::ModelComponent>();
	// gWorld.RegisterComponent<Player>();
	gWorld.RegisterComponent<Renderable>();
	gWorld.RegisterComponent<Gravity>();
	gWorld.RegisterComponent<RigidBody>();
	// gWorld.RegisterComponent<Thrust>();
	gWorld.RegisterComponent<Component::Transform>();

	mRenderSystem = gWorld.RegisterSystem<RenderSystem>(mainCamera);
	{
		Signature signature;
		signature.set(gWorld.GetComponentType<Renderable>());
		signature.set(gWorld.GetComponentType<Component::Transform>());
		gWorld.SetSystemSignature<RenderSystem>(signature);
	}

	mRenderSystem->Init();


	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);


	std::vector<Entity> entities(MAX_ENTITIES - 1);
    float scale = randScale(generator);

    	for (auto& entity : entities)
	{
		entity = gWorld.CreateEntity();

		gWorld.AddComponent<Gravity>(
			entity,
			{glm::vec3(0.0f, 9.8f, 0.0f)});

		gWorld.AddComponent(
			entity,
			RigidBody{
				.velocity = glm::vec3(0.0f, 0.0f, 0.0f),
				.acceleration = glm::vec3(0.0f, 0.0f, 0.0f)
			});

		gWorld.AddComponent(
			entity,
			Component::Transform(
				glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
				glm::quat(randRotation(generator), randRotation(generator), randRotation(generator), 0.0f),
				glm::vec3(scale, scale, scale)
			)
        );

		gWorld.AddComponent(
			entity,
			Renderable{
				.color = glm::vec3(randColor(generator), randColor(generator), randColor(generator))
			});
	}


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

        float hitDistance = 0.0F;
        PianoPhysics::Ray ray(mainCamera.Position, rayMouse);
        if (PianoPhysics::CheckRayToAABBIntersection(
                ray,
                cloudQuadObj.GetComponent<Component::BoundingBoxComponent>()
                    ->GetMinExtents(),
                cloudQuadObj.GetComponent<Component::BoundingBoxComponent>()
                    ->GetMaxExtents(),
                hitDistance)) {
            PianoCore::Log::Info("INTERSECTION at depth %4.2f", hitDistance);
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


    mRenderSystem->Update(0.05);

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
    // renderer.DrawObject(&cloudObj);
    glUniform1i(selectedLoc,
                cloudQuadObj.GetComponent<Component::SelectableComponent>()
                        ->IsSelected()
                    ? 1
                    : 0);
    renderer.DrawObject(&cloudQuadObj);

    // Debug line to draw the bounding box
    auto bb = cloudQuadObj.GetComponent<Component::BoundingBoxComponent>();
    bb->DrawDebug(projection, view);
}
void PianoAppGameLayer::Suspend() {
    PianoCore::Log::Info("Suspending PianoAppGameLayer");
}

PianoAppGameLayer::~PianoAppGameLayer() {
    PianoCore::Log::Info("Calling Destructor for PianoAppGameLayer");
}
}  // namespace PianoApp
