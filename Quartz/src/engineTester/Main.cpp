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

Camera camera(glm::vec3(0, 2, 0));

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

	// tree
	RawModel* treeRawModel = OBJLoader::loadOBJModel("res/models/tree.obj", &loader);
	Texture treeTexture("res/textures/tree.png");
	TexturedModel treeTexturedModel(treeRawModel, &treeTexture);
	glm::vec3 treePosition(10, 0, 10);
	glm::vec3 treeRotation(0, 0, 0);
	glm::vec3 treeScale(1, 1, 1);
	treeScale *= 5;
	Entity treeEntity(&treeTexturedModel, treePosition, treeRotation, treeScale);

	// grass
	RawModel* grassRawModel = OBJLoader::loadOBJModel("res/models/grass.obj", &loader);
	Texture grassTexture("res/textures/grass.png");
	grassTexture.setHasTransparency(true);
	grassTexture.setHas2DMesh(true);
	TexturedModel grassTexturedModel(grassRawModel, &grassTexture);
	glm::vec3 grassPosition(20, 0, 10);
	glm::vec3 grassRotation(0, 0, 0);
	glm::vec3 grassScale(1, 1, 1);
	Entity grassEntity(&grassTexturedModel, grassPosition, grassRotation, grassScale);

	// fern
	RawModel* fernRawModel = OBJLoader::loadOBJModel("res/models/fern.obj", &loader);
	Texture fernTexture("res/textures/fern.png");
	fernTexture.setHasTransparency(true);
	fernTexture.setHas2DMesh(true);
	TexturedModel fernTexturedModel(fernRawModel, &fernTexture);
	glm::vec3 fernPosition(10, 0, 20);
	glm::vec3 fernRotation(0, 0, 0);
	glm::vec3 fernScale(1, 1, 1);
	Entity fernEntity(&fernTexturedModel, fernPosition, fernRotation, fernScale);

	// Terrain
	Texture terrainTexture("res/textures/terrain.png");
	Terrain terrain1(0, 0, &loader, &terrainTexture);
	Terrain terrain2(1, 0, &loader, &terrainTexture);

	// Light
	glm::vec3 lightIntensity(1, 1, 1);
	lightIntensity *= 300;
	glm::vec3 lightPosition(20, 20, 20);
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
		masterRenderer.processEntity(&treeEntity);
		masterRenderer.processEntity(&grassEntity);
		masterRenderer.processEntity(&fernEntity);
		masterRenderer.processTerrain(&terrain1);
		masterRenderer.render(&light, &camera);

		// finish loop
		dm.finishLoop();
	}

	dm.close();
}