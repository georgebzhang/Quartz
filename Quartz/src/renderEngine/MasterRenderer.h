#pragma once

#include "../shaders/Shader.h"
#include "EntityRenderer.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"
#include "../renderEngine/TerrainRenderer.h"
#include "SkyRenderer.h"
#include "../models/CubeMapModel.h"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();

	static void enableCulling();
	static void disableCulling();

	void clear() const;
	void render(Light* light, Camera* camera);
	void processEntity(Entity* entity);
	void processTerrain(Terrain* terrain);
	inline void processSky(CubeMapModel* sky) { m_Sky = sky; }

	void loadUniforms(Shader* shader) const;

private:
	static const float FOV, NEAR_PLANE, FAR_PLANE;

	static const float SKY_R, SKY_G, SKY_B;

	glm::mat4 m_ProjectionMatrix;

	Shader* m_EntityShader;
	EntityRenderer* m_EntityRenderer;
	std::unordered_map<TexturedModel*, std::vector<Entity*>> m_Entities;

	Shader* m_TerrainShader;
	TerrainRenderer* m_TerrainRenderer;
	std::vector<Terrain*> m_Terrains;

	Shader* m_SkyShader;
	SkyRenderer* m_SkyRenderer;
	CubeMapModel* m_Sky;
};