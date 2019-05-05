#include "TerrainRenderer.h"
#include "../toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(Shader* shader, const glm::mat4 & projectionMatrix) : m_Shader(shader) {
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	loadUniforms(m_Shader); // sampler2Ds
	m_Shader->unbind();
}

void TerrainRenderer::render(const std::vector<Terrain*>& terrains) {
	for (Terrain* terrain : terrains) {
		bindTexturedModel(terrain);
		bindTerrain(terrain);
		GLCall(glDrawElements(GL_TRIANGLES, terrain->getRawModel()->getIB()->getCount(), GL_UNSIGNED_INT, (const void*)0));
		unbindTexturedModel(terrain);
	}
}

void TerrainRenderer::bindTextures(const Terrain* terrain) const {
	TexturePack* texturePack = terrain->getTexturePack();
	Texture* backgroundTexture = texturePack->getBackgroundTexture();
	backgroundTexture->bind();
	//m_Shader->setUniform1i("u_BackgroundTexture", 0);
	backgroundTexture->loadUniforms(m_Shader);

	Texture* rTexture = texturePack->getRTexture();
	rTexture->bind(1);
	//m_Shader->setUniform1i("u_RTexture", 1);
	rTexture->loadUniforms(m_Shader);

	Texture* gTexture = texturePack->getGTexture();
	gTexture->bind(2);
	//m_Shader->setUniform1i("u_GTexture", 2);
	gTexture->loadUniforms(m_Shader);

	Texture* bTexture = texturePack->getBTexture();
	bTexture->bind(3);
	//m_Shader->setUniform1i("u_BTexture", 3);
	bTexture->loadUniforms(m_Shader);

	Texture* blendMap = terrain->getBlendMap();
	blendMap->bind(4);
	//m_Shader->setUniform1i("u_BlendMap", 4);
	blendMap->loadUniforms(m_Shader);
}

void TerrainRenderer::bindTexturedModel(const Terrain* terrain) const {
	bindTextures(terrain);
	RawModel* rawModel = terrain->getRawModel();
	rawModel->getVA()->bind();
	rawModel->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
}

void TerrainRenderer::unbindTextures(const Terrain* terrain) const {
	TexturePack* texturePack = terrain->getTexturePack();
	texturePack->getBackgroundTexture()->unbind();
	texturePack->getRTexture()->unbind();
	texturePack->getGTexture()->unbind();
	texturePack->getBTexture()->unbind();
	terrain->getBlendMap()->unbind();
}

void TerrainRenderer::unbindTexturedModel(const Terrain* terrain) const {
	unbindTextures(terrain);
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

void TerrainRenderer::loadUniforms(Shader* shader) const {
	m_Shader->setUniform1i("u_BackgroundTexture", 0);
	m_Shader->setUniform1i("u_RTexture", 1);
	m_Shader->setUniform1i("u_GTexture", 2);
	m_Shader->setUniform1i("u_BTexture", 3);
	m_Shader->setUniform1i("u_BlendMap", 4);
}
