#include "../errors/ErrorHandler.h"
#include "Renderer.h"
#include "../toolbox/Maths.h"

#include "glm/gtc/matrix_transform.hpp"

#include <GL/glew.h>

Renderer::Renderer(Shader* shader) : m_Shader(shader) {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // optimization: does not render triangle that face inwards
	shader->bind();
	glm::mat4 projectionMatrix = glm::perspectiveFov(70.0f, 640.0f * 2, 480.0f * 2, 0.1f, 1000.0f);
	shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	shader->unbind();
}

void Renderer::clear() const {
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)); // considers depth
	GLCall(glClearColor(0.8, 0, 0, 1));
}

void Renderer::bindTexturedModel(const TexturedModel* texturedModel) const {
	Texture* texture = texturedModel->getTexture();
	texture->bind();
	m_Shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	texture->loadUniforms(m_Shader);
	RawModel* rawModel = texturedModel->getRawModel();
	rawModel->getVA()->bind();
	rawModel->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
}

void Renderer::unbindTexturedModel(const TexturedModel* texturedModel) const {
	Texture* texture = texturedModel->getTexture();
	texture->unbind();
	RawModel* rawModel = texturedModel->getRawModel();
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	rawModel->getIB()->unbind();
	rawModel->getVA()->unbind();
}

void Renderer::bindEntity(const Entity* entity) const {
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	m_Shader->setUniformMat4f("u_TransformationMatrix", transformationMatrix);
}

void Renderer::render(std::unordered_map<TexturedModel*, std::vector<Entity*>> entities) const {
	//for (const std::pair<TexturedModel*, std::vector<Entity*>> &pair : entities) {
	for (const auto &pair : entities) {
		TexturedModel* texturedModel = pair.first;
		bindTexturedModel(texturedModel);
		for (Entity* entity : pair.second) {
			bindEntity(entity);
			GLCall(glDrawElements(GL_TRIANGLES, texturedModel->getRawModel()->getIB()->getCount(), GL_UNSIGNED_INT, (const void*)0));
		}
	}
}
