#pragma once

#include <memory>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <ecs/System.h>
#include <shaders/IShader.h>
#include <components/Camera.h>

class Event;


class RenderSystem : public System
{
public:
    RenderSystem(const PerspectiveCamera& camera);
	void Init();
	void Update(float dt) override;

private:
	void WindowSizeListener(Event& event);

	std::shared_ptr<Shaders::IShader> shader;

	const PerspectiveCamera& mCamera;

	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
	GLuint mVbocolours{};
};
