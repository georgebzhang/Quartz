#pragma once

#include "../models/TexturedModel.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../shaders/Shader.h"

class Renderer {
public:
	void prepare() const;
	//void render(const RawModel* model) const;
	void render(const TexturedModel* texturedModel) const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};