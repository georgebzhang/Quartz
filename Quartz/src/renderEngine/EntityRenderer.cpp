#include "../errors/ErrorHandler.h"
#include "EntityRenderer.h"
#include "../toolbox/Maths.h"
#include "MasterRenderer.h"

#include <GL/glew.h>

EntityRenderer::EntityRenderer(Shader* shader, const glm::mat4& projectionMatrix) : m_Shader(shader) {
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	m_Shader->unbind();
}

void EntityRenderer::bindTexturedModel(const TexturedModel* texturedModel) const {
	Texture* texture = texturedModel->getTexture();
	if (texture->hasTransparency()) MasterRenderer::disableCulling();
	texture->bind();
	m_Shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	texture->loadUniforms(m_Shader);
	RawModel* rawModel = texturedModel->getRawModel();
	rawModel->getVA()->bind();
	if (rawModel->getIB() != nullptr)
		rawModel->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
}

void EntityRenderer::unbindTexturedModel(const TexturedModel* texturedModel) const {
	MasterRenderer::enableCulling();
	Texture* texture = texturedModel->getTexture();
	texture->unbind();
	RawModel* rawModel = texturedModel->getRawModel();
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	if (rawModel->getIB() != nullptr)
		rawModel->getIB()->unbind();
	rawModel->getVA()->unbind();
}

void EntityRenderer::bindEntity(const Entity* entity) const {
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	m_Shader->setUniformMat4f("u_TransformationMatrix", transformationMatrix);
}

void EntityRenderer::render(const std::unordered_map<TexturedModel*, std::vector<Entity*>>& entities) const {
	//for (const std::pair<TexturedModel*, std::vector<Entity*>> &pair : entities) {
	for (const auto &pair : entities) {
		TexturedModel* texturedModel = pair.first;
		bindTexturedModel(texturedModel);
		for (Entity* entity : pair.second) {
			bindEntity(entity);
			GLCall(glDrawElements(GL_TRIANGLES, texturedModel->getRawModel()->getIB()->getCount(), GL_UNSIGNED_INT, (const void*)0));
		}
		unbindTexturedModel(texturedModel);
	}
}
