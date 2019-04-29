#pragma once

#include "../models/TexturedModel.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"
#include "../shaders/Shader.h"

class Renderer {
public:
	void prepare();
	//void render(RawModel model);
	void render(TexturedModel texturedModel);
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};