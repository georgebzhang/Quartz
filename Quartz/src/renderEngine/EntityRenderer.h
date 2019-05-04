#pragma once

#include "../models/TexturedModel.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../entities/Entity.h"

class EntityRenderer {
public:
	EntityRenderer(Shader* shader, const glm::mat4& projectionMatrix);
	~EntityRenderer() { delete m_Shader; }

	void bindTexturedModel(const TexturedModel* texturedModel) const;
	void unbindTexturedModel(const TexturedModel* texturedModel) const;
	void bindEntity(const Entity* entity) const;
	void render(const std::unordered_map<TexturedModel*, std::vector<Entity*>>& entities) const;

private:
	Shader* m_Shader;
};