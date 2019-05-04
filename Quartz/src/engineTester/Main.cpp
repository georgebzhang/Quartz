#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/Shader.h"
#include "../models/TexturedModel.h"
#include "../errors/ErrorHandler.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../entities/Entity.h"
#include "../toolbox/Maths.h"
#include "../renderEngine/OBJLoader.h"
#include "../entities/Light.h"
#include "../renderEngine/MasterRenderer.h"

#include <iostream>

Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float speed = 0.5;
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W) camera.translate(speed * glm::vec3(0.0f, 0.0f, -1.0f));
	if (key == GLFW_KEY_S) camera.translate(speed * glm::vec3(0.0f, 0.0f, 1.0f));
	if (key == GLFW_KEY_A) camera.translate(speed * glm::vec3(-1.0f, 0.0f, 0.0f));
	if (key == GLFW_KEY_D) camera.translate(speed * glm::vec3(1.0f, 0.0f, 0.0f));
	if (key == GLFW_KEY_Q) camera.translate(speed * glm::vec3(0.0f, -1.0f, 0.0f));
	if (key == GLFW_KEY_E) camera.translate(speed * glm::vec3(0.0f, 1.0f, 0.0f));
}

int main(void) {
	DisplayManager dm;
	dm.open();

	Loader loader;

	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	RawModel* rawModel = OBJLoader::loadOBJModel("res/models/dragon.obj", &loader);
	Texture texture("res/textures/white.png");
	TexturedModel texturedModel(rawModel, &texture);

	// light
	glm::vec3 intensity(1.0f, 1.0f, 1.0f);
	intensity *= 700;
	glm::vec3 position(0.0f, 0.0f, -20.0f);
	glm::vec3 color(0.0f, 1.0f, 1.0f);
	Light light(intensity, position, color);

	std::vector<Entity*> dragons;
	for (int i = 0; i < 25; ++i) {
		glm::vec3 position(Maths::randFloat() * 100 - 50, Maths::randFloat() * 100 - 50, Maths::randFloat() * -300);
		glm::vec3 rotation(Maths::randFloat() * 180, Maths::randFloat() * 180, 0.0f);
		glm::vec3 scale(1.0f, 1.0f, 1.0f);
		scale *= Maths::randFloat() * 2;
		dragons.emplace_back(new Entity(&texturedModel, position, rotation, scale)); // new used here, since Entity(...) goes out of scope after for loop
	}
	
	MasterRenderer masterRenderer;

	while (dm.isOpen()) {
		// render
		for (Entity* dragon : dragons) {
			masterRenderer.processEntity(dragon);
		}
		masterRenderer.render(&light, &camera);

		// finish loop
		dm.finishLoop();
	}

	dm.close();
}