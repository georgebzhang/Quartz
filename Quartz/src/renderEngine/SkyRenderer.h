#pragma once

#include "../shaders/Shader.h"
#include "../models/CubeMapModel.h"
#include "../models/TexturedModel.h"

class SkyRenderer {
public:
	SkyRenderer(Shader* shader, const glm::mat4& projectionMatrix);
	~SkyRenderer() { delete m_Shader; }

	void render(CubeMapModel* sky) const;
	void render(TexturedModel* sky) const;

private:
	Shader* m_Shader;
};