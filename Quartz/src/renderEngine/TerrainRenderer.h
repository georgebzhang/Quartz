#pragma once

#include "../shaders/Shader.h"
#include "../terrains/Terrain.h"

class TerrainRenderer {
public:
	TerrainRenderer(Shader* shader, const glm::mat4& projectionMatrix);
	~TerrainRenderer() { delete m_Shader; }

	void render(const std::vector<Terrain*>& terrains);

private:
	Shader* m_Shader;

	void bindTextures(const Terrain* terrain) const;
	void bindTexturedModel(const Terrain* terrain) const;

	void unbindTextures(const Terrain* terrain) const;
	void unbindTexturedModel(const Terrain* terrain) const;

	void bindTerrain(const Terrain* terrain) const;

	void loadUniforms(Shader* shader) const;
};