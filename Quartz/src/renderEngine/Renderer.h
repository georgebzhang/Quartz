#pragma once

#include "../models/TexturedModel.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../shaders/Shader.h"
#include "../entities/Entity.h"

class Renderer {
public:
	Renderer(Shader* shader);
	~Renderer() {}

	void clear() const;

	void bindTexturedModel(const TexturedModel* texturedModel) const;
	void unbindTexturedModel(const TexturedModel* texturedModel) const;
	void bindEntity(const Entity* entity) const;
	void render(std::unordered_map<TexturedModel*, std::vector<Entity*>> entities) const;

private:
	Shader* m_Shader;
};