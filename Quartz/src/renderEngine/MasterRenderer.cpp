#include "MasterRenderer.h"

#include "glm/gtc/matrix_transform.hpp"

const float MasterRenderer::FOV = 70;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000;

MasterRenderer::MasterRenderer() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // optimization: does not render triangle that face inwards
	m_ProjectionMatrix = glm::perspectiveFov(FOV, 640.0f * 2, 480.0f * 2, NEAR_PLANE, FAR_PLANE);
	m_EntityShader = new Shader("res/shaders/entityVert.shader", "res/shaders/entityFrag.shader");
	m_EntityRenderer = new EntityRenderer(m_EntityShader, m_ProjectionMatrix);
	m_TerrainShader = new Shader("res/shaders/terrainVert.shader", "res/shaders/terrainFrag.shader");
	m_TerrainRenderer = new TerrainRenderer(m_TerrainShader, m_ProjectionMatrix);
}

MasterRenderer::~MasterRenderer() {
	delete m_EntityShader;
	delete m_EntityRenderer;
	// handle hashmap deletion
}

void MasterRenderer::clear() const {
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // considers depth
	GLCall(glClearColor(0.8, 0, 0, 1));
}

void MasterRenderer::render(Light* light, Camera* camera) {
	clear();
	m_EntityShader->bind();
	light->loadUniforms(m_EntityShader);
	camera->loadUniforms(m_EntityShader);
	m_EntityRenderer->render(m_Entities);
	m_EntityShader->unbind();

	m_TerrainShader->bind();
	light->loadUniforms(m_TerrainShader);
	camera->loadUniforms(m_TerrainShader);
	m_TerrainRenderer->render(m_Terrains);
	m_TerrainShader->unbind();

	m_Entities.clear();
	m_Terrains.clear();
}

void MasterRenderer::processEntity(Entity* entity) {
	TexturedModel* texturedModel = entity->getTexturedModel();
	if (m_Entities.find(texturedModel) != m_Entities.end()) {
		m_Entities[texturedModel].emplace_back(entity);
	} else {
		m_Entities[texturedModel] = std::vector<Entity*>{ entity };
	}
}

void MasterRenderer::processTerrain(Terrain* terrain) {
	m_Terrains.emplace_back(terrain);
}
