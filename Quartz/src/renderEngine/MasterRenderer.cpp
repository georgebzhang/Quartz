#include "MasterRenderer.h"

#include "glm/gtc/matrix_transform.hpp"

const float MasterRenderer::FOV = 70;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000;

const float MasterRenderer::SKY_R = 0.5f;
const float MasterRenderer::SKY_G = 0.5f;
const float MasterRenderer::SKY_B = 0.5f;

MasterRenderer::MasterRenderer() {
	enableCulling();
	m_ProjectionMatrix = glm::perspectiveFov(FOV, 640.0f * 3, 480.0f * 3, NEAR_PLANE, FAR_PLANE);
	//m_EntityShader = new Shader("res/shaders/entityVert.shader", "res/shaders/entityFrag.shader");
	m_EntityShader = new Shader("res/shaders/glassVert.shader", "res/shaders/glassFrag.shader");
	m_EntityRenderer = new EntityRenderer(m_EntityShader, m_ProjectionMatrix);
	m_TerrainShader = new Shader("res/shaders/terrainVert.shader", "res/shaders/terrainFrag.shader");
	m_TerrainRenderer = new TerrainRenderer(m_TerrainShader, m_ProjectionMatrix);
	m_SkyShader = new Shader("res/shaders/skyVert.shader", "res/shaders/skyFrag.shader");
	m_SkyRenderer = new SkyRenderer(m_SkyShader, m_ProjectionMatrix);
}

MasterRenderer::~MasterRenderer() {
	delete m_EntityShader;
	delete m_EntityRenderer;
	// handle hashmap deletion
}

void MasterRenderer::enableCulling() {
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK)); // optimization: does not render triangle that face inwards
}

void MasterRenderer::disableCulling() {
	GLCall(glDisable(GL_CULL_FACE));
}

void MasterRenderer::clear() const {
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // considers depth
	GLCall(glClearColor(SKY_R, SKY_G, SKY_B, 1));
}

void MasterRenderer::render(Light* light, Camera* camera) {
	clear();
	m_TerrainShader->bind();
	light->loadUniforms(m_TerrainShader);
	camera->loadUniforms(m_TerrainShader);
	loadUniforms(m_TerrainShader); // sky
	m_TerrainRenderer->render(m_Terrains);
	m_TerrainShader->unbind();

	m_EntityShader->bind();
	light->loadUniforms(m_EntityShader);
	camera->loadUniforms(m_EntityShader);
	loadUniforms(m_EntityShader); // sky
	m_EntityRenderer->render(m_Entities);
	m_EntityShader->unbind();

	//glDepthFunc(GL_LEQUAL);
	m_SkyShader->bind();
	camera->loadUniforms2(m_SkyShader);
	m_SkyRenderer->render(m_Sky);
	m_SkyShader->unbind();
	//glDepthFunc(GL_LESS);

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

void MasterRenderer::loadUniforms(Shader* shader) const {
	shader->setUniform3fv("u_SkyColor", glm::vec3(SKY_R, SKY_G, SKY_B));
	shader->setUniform1i("u_SkyBox", 0);
}
