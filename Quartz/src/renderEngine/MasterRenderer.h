#pragma once

#include "../shaders/Shader.h"
#include "Renderer.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"

class MasterRenderer {
public:
	MasterRenderer() {}
	~MasterRenderer();

	void render(Light* light, Camera* camera);
	void processEntity(Entity* entity);

private:
	Shader* m_Shader = new Shader("res/shaders/entity.vert", "res/shaders/entity.frag");
	Renderer* m_Renderer = new Renderer(m_Shader);
	std::unordered_map<TexturedModel*, std::vector<Entity*>> m_Entities;
};