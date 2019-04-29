#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/Shader.h"
#include "../models/TexturedModel.h"
#include "../errors/ErrorHandler.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"

#include <iostream>

int main(void) {
	DisplayManager::open();

	Loader loader;
	Renderer renderer;
	Shader shader("res/shaders/vertexShader.shader", "res/shaders/fragmentShader.shader");

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

	//RawModel model = loader.loadToVAO(vertices, p_count, indices, i_count);
	RawModel* model = loader.loadToVAO(vertices, p_count, texCoords, t_count, indices, i_count);
	//std::cout << &model << std::endl;
	//std::cout << model.getVAOID() << std::endl;
	//std::cout << model.getVertexCount() << std::endl;

	shader.bind();
	Texture texture("res/textures/image.png");
	texture.Bind();
	shader.setUniform1i("u_Texture", 0); // read texture from slot 0
	shader.unbind();

	//TexturedModel texturedModel(model, texture);
	//std::cout << &(texturedModel.getRawModel()) << std::endl;
	//std::cout << texturedModel.getRawModel().getVAOID() << std::endl;
	//std::cout << texturedModel.getRawModel().getVertexCount() << std::endl;

	while (DisplayManager::isActive()) {
		/* Render here */
		renderer.prepare();
		shader.bind();

		//renderer.draw(va, ib, shader);
		renderer.render(model);
		//renderer.render(texturedModel);

		shader.unbind();
		DisplayManager::finishLoop();
	}

	//shader.cleanUp();
	//loader.cleanUp();

	DisplayManager::close();
}