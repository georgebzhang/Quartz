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

#include <iostream>

Camera* camera = new Camera(glm::vec3(0.0f, 3.0f, 0.0f));

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W) camera->translate(glm::vec3(0.0f, 0.0f, -0.2f));
	if (key == GLFW_KEY_S) camera->translate(glm::vec3(0.0f, 0.0f, 0.2f));
	if (key == GLFW_KEY_A) camera->translate(glm::vec3(0.2f, 0.0f, 0.0f));
	if (key == GLFW_KEY_D) camera->translate(glm::vec3(-0.2f, 0.0f, 0.0f));
}

int main(void) {
	DisplayManager dm;
	dm.open();

	Loader* loader = new Loader();
	Shader* shader = new Shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");
	Renderer renderer(shader);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	RawModel* rawModel = OBJLoader::loadOBJModel("res/models/dragon.obj", loader);

	shader->bind();
	Texture* texture = new Texture("res/textures/white.png");
	texture->bind();
	shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	texture->loadUniforms(shader);
	shader->unbind();

	TexturedModel* texturedModel = new TexturedModel(rawModel, texture);
	glm::vec3 position(0.0f, 0.0f, -25.0f);
	glm::vec3 rotation(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	Entity* entity = new Entity(texturedModel, position, rotation, scale);

	glm::vec3 intensity(1.0f, 1.0f, 1.0f);
	intensity *= 10;
	glm::vec3 position2(0.0f, 5.0f, -20.0f);
	glm::vec3 color(0.0f, 1.0f, 1.0f);
	Light* light = new Light(intensity, position2, color);

	while (dm.isOpen()) {
		/* Render here */
		//entity->translate(glm::vec3(0.0f, 0.0f, -0.01f));
		entity->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
		renderer.prepare();
		shader->bind();

		light->loadUniforms(shader);
		camera->loadUniforms(shader);

		renderer.render(entity, shader);

		shader->unbind();
		dm.finishLoop();
	}

	dm.close();
}