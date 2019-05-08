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
#include "../entities/Player.h"

#include <iostream>

#define LOG(x) std::cout << x << std::endl;

Player* player;
Camera* camera;
bool mouseLeftPressed = false, mouseRightPressed = false;

bool posUnitialized = true;
float lastXPos = 0, lastYPos = 0;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float speed = 3;
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;

	// player
	case GLFW_KEY_W:
		player->run(true);
		switch (action) {
		case GLFW_RELEASE:
			player->stopMove();
			break;
		}
		break;
	case GLFW_KEY_S:
		player->run(false);
		switch (action) {
		case GLFW_RELEASE:
			player->stopMove();
			break;
		}
		break;
	case GLFW_KEY_A:
		player->turn(true);
		switch (action) {
		case GLFW_RELEASE:
			player->stopTurn();
			break;
		}
		break;
	case GLFW_KEY_D:
		player->turn(false);
		switch (action) {
		case GLFW_RELEASE:
			player->stopTurn();
			break;
		}
		break;
	case GLFW_KEY_SPACE:
		player->jump();
		break;

	// camera
	//case GLFW_KEY_UP:
	//	camera->translate(speed * glm::vec3(0, 0, -1));
	//	break;
	//case GLFW_KEY_DOWN:
	//	camera->translate(speed * glm::vec3(0, 0, 1));
	//	break;
	//case GLFW_KEY_LEFT:
	//	camera->translate(speed * glm::vec3(-1, 0, 0));
	//	break;
	//case GLFW_KEY_RIGHT:
	//	camera->translate(speed * glm::vec3(1, 0, 0));
	//	break;
	//case GLFW_KEY_PAGE_UP:
	//	camera->translate(speed * glm::vec3(0, -1, 0));
	//	break;
	//case GLFW_KEY_PAGE_DOWN:
	//	camera->translate(speed * glm::vec3(0, 1, 0));
	//	break;
	}
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	if (posUnitialized) {
		lastXPos = xpos;
		lastYPos = ypos;
		posUnitialized = false;
		return;
	}
	float dx = xpos - lastXPos;
	float dy = ypos - lastYPos;
	if (mouseLeftPressed) {
		camera->updateAngle(dx * 0.1f);
		camera->updatePitch(-dy * 0.1f);
	}
	lastXPos = xpos;
	lastYPos = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseLeftPressed = true;
		switch (action) {
		case GLFW_PRESS:
			mouseLeftPressed = true;
			break;
		case GLFW_RELEASE:
			mouseLeftPressed = false;
			break;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseRightPressed = true;
		switch (action) {
		case GLFW_PRESS:
			mouseRightPressed = true;
			break;
		case GLFW_RELEASE:
			mouseRightPressed = false;
			break;
		}
		break;
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera->updateZoom(yoffset);
}


int main(void) {
	DisplayManager::open();
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Loader loader;

	Texture backgroundTexture("res/textures/grassy.png");
	Texture rTexture("res/textures/dirt.png");
	Texture gTexture("res/textures/pinkFlowers.png");
	Texture bTexture("res/textures/path.png");
	TexturePack texturePack(&backgroundTexture, &rTexture, &gTexture, &bTexture);
	Texture blendMap("res/textures/blendMap.png");

	RawModel* playerRawModel = OBJLoader::loadOBJModel("res/models/sphere.obj", &loader);
	Texture playerTexture("res/textures/white.png");
	TexturedModel playerTexturedModel(playerRawModel, &playerTexture);
	glm::vec3 playerPosition(20, 0, -20);
	glm::vec3 playerRotation(0, 0, 0);
	glm::vec3 playerScale(1, 1, 1);
	playerScale *= 0.5;
	player = new Player(&playerTexturedModel, playerPosition, playerRotation, playerScale);
	camera = new Camera(player);

	int side_count = 5;
	int separation = 50;

	// tree
	RawModel* treeRawModel = OBJLoader::loadOBJModel("res/models/tree.obj", &loader);
	Texture treeTexture("res/textures/tree.png");
	TexturedModel treeTexturedModel(treeRawModel, &treeTexture);
	std::vector<Entity*> trees;
	for (int j = 0; j < side_count; ++j) {
		for (int i = 0; i < side_count; ++i) {
			trees.emplace_back(new Entity(&treeTexturedModel, glm::vec3(i*separation, 0, -j * separation), glm::vec3(0, 0, 0), 5.0f * glm::vec3(1, 1, 1)));
		}
	}

	// grass
	RawModel* grassRawModel = OBJLoader::loadOBJModel("res/models/grass.obj", &loader);
	Texture grassTexture("res/textures/grass.png");
	grassTexture.setHasTransparency(true);
	grassTexture.setHas2DMesh(true);
	TexturedModel grassTexturedModel(grassRawModel, &grassTexture);
	std::vector<Entity*> grasses;
	for (int j = 0; j < side_count; ++j) {
		for (int i = 0; i < side_count; ++i) {
			grasses.emplace_back(new Entity(&grassTexturedModel, glm::vec3(10 + i * separation, 0, -j * separation), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
		}
	}

	// fern
	RawModel* fernRawModel = OBJLoader::loadOBJModel("res/models/fern.obj", &loader);
	Texture fernTexture("res/textures/fern.png");
	fernTexture.setHasTransparency(true);
	fernTexture.setHas2DMesh(true);
	TexturedModel fernTexturedModel(fernRawModel, &fernTexture);
	std::vector<Entity*> ferns;
	for (int j = 0; j < side_count; ++j) {
		for (int i = 0; i < side_count; ++i) {
			ferns.emplace_back(new Entity(&fernTexturedModel, glm::vec3(20 + i * separation, 0, -j * separation), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
		}
	}

	// Terrain
	Texture terrainTexture("res/textures/terrain.png");
	std::vector<Terrain*> terrains;
	for (int j = -2; j < 0; ++j) {
		for (int i = 0; i < 2; ++i) {
			terrains.emplace_back(new Terrain(i, j, &loader, &texturePack, &blendMap));
		}
	}

	// Light
	glm::vec3 lightIntensity(1, 1, 1);
	lightIntensity *= 300;
	glm::vec3 lightPosition(20, 20, -20);
	glm::vec3 lightColor(1, 1, 1);
	Light light(lightIntensity, lightPosition, lightColor);
	
	MasterRenderer masterRenderer;

	while (DisplayManager::isOpen()) {
		// render
		player->move();
		camera->move();
		masterRenderer.processEntity(player);
		for (Entity* tree : trees) masterRenderer.processEntity(tree);
		for (Entity* grass : grasses) masterRenderer.processEntity(grass);
		for (Entity* fern : ferns) masterRenderer.processEntity(fern);
		for (Terrain* terrain : terrains) masterRenderer.processTerrain(terrain);
		masterRenderer.render(&light, camera);

		// finish loop
		DisplayManager::finishLoop();
	}

	DisplayManager::close();
}