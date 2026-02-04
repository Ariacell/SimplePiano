#include "RenderSystem.h"

#include <components/Transform.h>
#include "../components/Renderable.h"
#include <ecs/World.h>
#include <cmath>
#include <shaders/OpenGlShader.h>


extern World gWorld;


RenderSystem::RenderSystem(const PerspectiveCamera& camera) : mCamera(camera)
{
}

void RenderSystem::Init()
{
	// gWorld.AddEventListener(METHOD_LISTENER(Events::Window::RESIZED, RenderSystem::WindowSizeListener));

	shader = std::make_shared<Shaders::OpenGlShader>(
        "./shaders/cube.vert", "./shaders/cube.frag");
	std::vector<glm::vec3> vertices =
		{
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5),
			glm::vec3(0.5f, -0.5f, 0.5),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(-0.5f, 0.5f, 0.5),
			glm::vec3(-0.5f, -0.5f, 0.5),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(0.5f, 0.5f, -0.5),
			glm::vec3(0.5f, -0.5f, -0.5),
			glm::vec3(0.5f, -0.5f, -0.5),
			glm::vec3(0.5f, -0.5f, 0.5),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5),
			glm::vec3(0.5f, 0.5f, -0.5),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(0.5f, 0.5f, 0.5),
			glm::vec3(-0.5f, 0.5f, 0.5),
			glm::vec3(-0.5f, 0.5f, -0.5)
		};

	std::vector<glm::vec3> normals =
		{
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0)
		};

		

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// Vertices
	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
	glEnableVertexAttribArray(0);

	// Surface normal
	glGenBuffers(1, &mVboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RenderSystem::Update(float dt)
{
    std::cout << "Updating Render System" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT (hicpp-signed-bitwise)
    glEnable(GL_DEPTH_TEST);
	shader->use();
	glBindVertexArray(mVao);


	auto& viewMatrix = mCamera.GetViewMatrix();

	for (auto const& entity : mEntities)
	{
		auto const& transform = gWorld.GetComponent<Component::Transform>(entity);
		auto const& renderable = gWorld.GetComponent<Renderable>(entity);

		glm::mat4 model(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::rotate(model, transform.rotation.y, {0,1,0}); 
        model = glm::scale(model, transform.scale);

		glm::mat4 projection = glm::perspective(
        glm::radians(45.0F),
        (float)1980.0 / (float)1200.0, 0.1F,
        100.0F);


		unsigned int viewLoc = glGetUniformLocation(shader->GetID(), "view");
        unsigned int projLoc =
        glGetUniformLocation(shader->GetID(), "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        unsigned int selectedLoc =
        glGetUniformLocation(shader->GetID(), "isSelected");
		// shader->SetUniform<glm::mat4>("uModel", model);
		// shader->SetUniform<glm::mat4>("uView", view);
		// shader->SetUniform<glm::mat4>("uProjection", projection);

        unsigned int modelLoc =
        glGetUniformLocation(shader->GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}

void RenderSystem::WindowSizeListener(Event& event)
{
	// auto windowWidth = event.GetParam<unsigned int>(Events::Window::Resized::WIDTH);
	// auto windowHeight = event.GetParam<unsigned int>(Events::Window::Resized::HEIGHT);

	// auto& camera = gWorld.GetComponent<Camera>(mCamera);
	// camera.projectionTransform = Camera::MakeProjectionTransform(45.0f, 0.1f, 1000.0f, windowWidth, windowHeight);
}

