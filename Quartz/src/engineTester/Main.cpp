#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/Shader.h"
#include "../models/TexturedModel.h"
#include "../errors/ErrorHandler.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../entities/Entity.h"

#include <iostream>

int main(void) {
	DisplayManager::open();

	Loader loader;
	Shader* shader = new Shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");
	Renderer renderer(shader);

	//float vertices[] = {
	//	-0.5f, 0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,
	//};

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f,
	//	-0.5f, 0.5f, 0.0f,
	//};

	float vertices[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	//int indices[] = {
	//	0, 1, 3,
	//	3, 1, 2
	//};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//float textureCoords[] = {
	//	0, 0,
	//	0, 1,
	//	1, 1,
	//	1, 0
	//};

	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	int p_count = sizeof(vertices) / sizeof(vertices[0]);
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

	RawModel* rawModel = loader.loadToVAO(vertices, p_count, texCoords, t_count, indices, i_count);

	shader->bind();
	Texture* texture = new Texture("res/textures/image.png");
	texture->bind();
	shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	shader->unbind();

	TexturedModel* texturedModel = new TexturedModel(rawModel, texture);
	glm::vec3 position(0.0f, 0.0f, -1.0f);
	glm::vec3 rotation(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	Entity* entity = new Entity(texturedModel, position, rotation, scale);

	while (DisplayManager::isActive()) {
		/* Render here */
		entity->translate(glm::vec3(0.0f, 0.0f, -0.1f));
		//entity->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
		renderer.prepare();
		shader->bind();

		//renderer.draw(va, ib, shader);
		//renderer.render(rawModel);
		//renderer.render(texturedModel);
		renderer.render(entity, shader);

		shader->unbind();
		DisplayManager::finishLoop();
	}

	DisplayManager::close();
}