#include "TerrainRenderer.h"
#include "../toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(Shader* shader, const glm::mat4 & projectionMatrix) : m_Shader(shader) {
	shader->bind();
	shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	shader->unbind();
}

void TerrainRenderer::render(const std::vector<Terrain*>& terrains) {
	for (Terrain* terrain : terrains) {
		bindTexturedModel(terrain);
		bindTerrain(terrain);
		GLCall(glDrawElements(GL_TRIANGLES, terrain->getRawModel()->getIB()->getCount(), GL_UNSIGNED_INT, (const void*)0));
		unbindTexturedModel(terrain);
	}
}

void TerrainRenderer::bindTexturedModel(const Terrain* terrain) const {
	Texture* texture = terrain->getTexture();
	texture->bind();
	m_Shader->setUniform1i("u_Texture", 0); // read texture from slot 0
	texture->loadUniforms(m_Shader);
	RawModel* rawModel = terrain->getRawModel();
	rawModel->getVA()->bind();
	rawModel->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
}

void TerrainRenderer::unbindTexturedModel(const Terrain* terrain) const {
	Texture* texture = terrain->getTexture();
	texture->unbind();
	RawModel* rawModel = terrain->getRawModel();
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	rawModel->getIB()->unbind();
	rawModel->getVA()->unbind();
}

void TerrainRenderer::bindTerrain(const Terrain* terrain) const {
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(terrain->getPosition(), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	m_Shader->setUniformMat4f("u_TransformationMatrix", transformationMatrix);
}