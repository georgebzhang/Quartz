#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"
#include "../models/TexturedModel.h"
#include "../errors/ErrorHandler.h"

#include <iostream>

int main(void) {
	DisplayManager::open();

	Loader loader;
	Renderer renderer;
	StaticShader shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");

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

	//int indices[] = {
	//	0, 1, 3,
	//	3, 1, 2
	//};

	int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//float textureCoords[] = {
	//	0, 0,
	//	0, 1,
	//	1, 1,
	//	1, 0
	//};

	float textureCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	int p_count = sizeof(vertices) / sizeof(vertices[0]);
	int i_count = sizeof(indices) / sizeof(indices[0]);
	int t_count = sizeof(textureCoords) / sizeof(textureCoords[0]);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//RawModel model = loader.loadToVAO(vertices, p_count, indices, i_count);
	RawModel model = loader.loadToVAO(vertices, p_count, textureCoords, t_count, indices, i_count);

	shader.start();

	//Texture texture = loader.loadTexture("res/textures/Chernologo.png");
	Texture texture("res/textures/Chernologo.png");
	//std::cout << &texture << std::endl;
	//std::cin.get();
	texture.Bind();
	//shader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
	shader.SetUniform1i("u_Texture", 0); // read texture from slot 0

	//shader.stop();

	TexturedModel texturedModel(model, texture);

	while (DisplayManager::isActive()) {
		/* Render here */
		renderer.prepare();
		shader.start();

		renderer.render(model);

		//shader.stop();

		DisplayManager::update();
	}

	shader.cleanUp();
	loader.cleanUp();

	DisplayManager::close();
}