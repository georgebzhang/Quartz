#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"

#include <iostream>

int main(void) {
	DisplayManager::open();

	Loader loader;
	Renderer renderer;
	StaticShader shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	int indices[] = {
		0, 1, 3,
		3, 1, 2
	};

	int p_count = sizeof(vertices) / sizeof(vertices[0]);
	int i_count = sizeof(indices) / sizeof(indices[0]);

	RawModel model = loader.loadToVAO(vertices, p_count, indices, i_count);

	while (DisplayManager::isActive()) {
		/* Render here */
		renderer.prepare();
		shader.start();
		renderer.render(model);
		shader.stop();

		DisplayManager::update();
	}

	shader.cleanUp();
	loader.cleanUp();

	DisplayManager::close();
}