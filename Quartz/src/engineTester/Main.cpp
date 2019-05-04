#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/EntityRenderer.h"
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

Camera camera(glm::vec3(0, 3, 20));

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float speed = 0.5;
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W) camera.translate(speed * glm::vec3(0, 0, -1));
	if (key == GLFW_KEY_S) camera.translate(speed * glm::vec3(0, 0, 1));
	if (key == GLFW_KEY_A) camera.translate(speed * glm::vec3(-1, 0, 0));
	if (key == GLFW_KEY_D) camera.translate(speed * glm::vec3(1, 0, 0));
	if (key == GLFW_KEY_Q) camera.translate(speed * glm::vec3(0, -1, 0));
	if (key == GLFW_KEY_E) camera.translate(speed * glm::vec3(0, 1, 0));
	if (key == GLFW_KEY_E) camera.translate(speed * glm::vec3(0, 1, 0));
}

int main(void) {
	DisplayManager dm;
	dm.open();

	Loader loader;

	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// TexturedModel
	RawModel* rawModel = OBJLoader::loadOBJModel("res/models/dragon.obj", &loader);
	Texture texture("res/textures/white.png");
	TexturedModel texturedModel(rawModel, &texture);

	// Entity
	glm::vec3 entityPosition(0, 0, 0);
	glm::vec3 entityRotation(0, 0, 0);
	glm::vec3 entityScale(1, 1, 1);
	Entity entity(&texturedModel, entityPosition, entityRotation, entityScale);

	// Light
	glm::vec3 lightIntensity(1, 1, 1);
	lightIntensity *= 100;
	glm::vec3 lightPosition(0, 0, 20);
	glm::vec3 lightColor(0, 1, 1);
	Light light(lightIntensity, lightPosition, lightColor);

	//std::vector<Entity*> dragons;
	//for (int i = 0; i < 25; ++i) {
	//	glm::vec3 position(Maths::randFloat() * 100 - 50, Maths::randFloat() * 100 - 50, Maths::randFloat() * -300);
	//	glm::vec3 rotation(Maths::randFloat() * 180, Maths::randFloat() * 180, 0.0f);
	//	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	//	scale *= Maths::randFloat() * 2;
	//	dragons.emplace_back(new Entity(&texturedModel, position, rotation, scale)); // new used here, since Entity(...) goes out of scope after for loop
	//}
	
	MasterRenderer masterRenderer;

	while (dm.isOpen()) {
		// render
		//for (Entity* dragon : dragons) {
		//	masterRenderer.processEntity(dragon);
		//}
		masterRenderer.processEntity(&entity);
		masterRenderer.render(&light, &camera);

		// finish loop
		dm.finishLoop();
	}

	dm.close();
}