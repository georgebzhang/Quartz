#include "MasterRenderer.h"

MasterRenderer::~MasterRenderer() {
	delete m_Shader;
	delete m_Renderer;
	// handle hashmap deletion
}

void MasterRenderer::render(Light* light, Camera* camera) {
	m_Renderer->clear();
	m_Shader->bind();
	light->loadUniforms(m_Shader);
	camera->loadUniforms(m_Shader);
	m_Renderer->render(m_Entities);
	m_Shader->unbind();
	m_Entities.clear();
}

void MasterRenderer::processEntity(Entity* entity) {
	TexturedModel* texturedModel = entity->getTexturedModel();
	if (m_Entities.find(texturedModel) != m_Entities.end()) {
		m_Entities[texturedModel].emplace_back(entity);
	} else {
		m_Entities[texturedModel] = std::vector<Entity*>{ entity };
	}
}
