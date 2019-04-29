#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/Shader.h"
#include "../models/TexturedModel.h"
#include "../errors/ErrorHandler.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../entities/Entity.h"
#include "../entities/Camera.h"
#include "../toolbox/Maths.h"

#include <iostream>


Camera* camera = new Camera();

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//std::cout << key << std::endl;
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W) {
		camera->translate(glm::vec3(0.0f, 0.0f, -0.05f));
	}
	if (key == GLFW_KEY_S) {
		camera->translate(glm::vec3(0.0f, 0.0f, 0.05f));
	}
	if (key == GLFW_KEY_A) {
		camera->translate(glm::vec3(0.05f, 0.0f, 0.0f));
	}
	if (key == GLFW_KEY_D) {
		camera->translate(glm::vec3(-0.05f, 0.0f, 0.0f));
	}
}

int main(void) {
	DisplayManager dm;
	dm.open();

	Loader loader;
	Shader* shader = new Shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");
	Renderer renderer(shader);

	//float positions[] = {
	//	-0.5f, -0.5f,
	//	0.5f, -0.5f,
	//	0.5f, 0.5f,
	//	-0.5f, 0.5f
	//};

	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	//float texCoords[] = {
	//	0.0f, 0.0f,
	//	1.0f, 0.0f,
	//	1.0f, 1.0f,
	//	0.0f, 1.0f
	//};

	float positions[] = {
				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,0.5f,-0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,-0.5f,0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				0.5f,0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f,-0.5f,0.5f,
				-0.5f,0.5f,0.5f,

				-0.5f,0.5f,0.5f,
				-0.5f,0.5f,-0.5f,
				0.5f,0.5f,-0.5f,
				0.5f,0.5f,0.5f,

				-0.5f,-0.5f,0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,0.5f
	};

	float texCoords[] = {
			0,0,
			0,1,
			1,1,
			1,0,
			0,0,
			0,1,
			1,1,
			1,0,
			0,0,
			0,1,
			1,1,
			1,0,
			0,0,
			0,1,
			1,1,
			1,0,
			0,0,
			0,1,
			1,1,
			1,0,
			0,0,
			0,1,
			1,1,
			1,0
	};

	unsigned int indices[] = {
			0,1,3,
			3,1,2,
			4,5,7,
			7,5,6,
			8,9,11,
			11,9,10,
			12,13,15,
			15,13,14,
			16,17,19,
			19,17,18,
			20,21,23,
			23,21,22
	};

	int p_count = sizeof(positions) / sizeof(positions[0]);
	int i_count = sizeof(indices) / sizeof(indices[0]);
	int t_count = sizeof(texCoords) / sizeof(texCoords[0]);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//VertexArray va;
	//VertexBuffer vb0(positions, p_count * sizeof(float));
	//va.addBuffer(vb0, 0, 2);
	//VertexBuffer vb1(texCoords, t_count * sizeof(float));
	//va.addBuffer(vb1, 1, 2);
	//IndexBuffer ib(indices, i_count);

	RawModel* rawModel = loader.loadToVAO(positions, p_count, texCoords, t_count, indices, i_count);

	shader->bind();
	Texture* texture = new Texture("res/textures/image.png");
	texture->bind();
	shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	shader->unbind();

	TexturedModel* texturedModel = new TexturedModel(rawModel, texture);
	glm::vec3 position(0.0f, 0.0f, -5.0f);
	glm::vec3 rotation(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	Entity* entity = new Entity(texturedModel, position, rotation, scale);


	while (dm.isActive()) {
		/* Render here */
		//entity->translate(glm::vec3(0.0f, 0.0f, -0.01f));
		entity->rotate(glm::vec3(1.0f, 1.0f, 0.0f));
		renderer.prepare();
		shader->bind();

		glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
		shader->setUniformMat4f("u_ViewMatrix", viewMatrix);
		//renderer.draw(va, ib, shader);
		//renderer.render(rawModel);
		//renderer.render(texturedModel);
		renderer.render(entity, shader);

		shader->unbind();
		dm.finishLoop();
	}

	dm.close();
}