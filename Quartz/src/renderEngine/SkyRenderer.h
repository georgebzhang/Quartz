#pragma once

#include "../shaders/Shader.h"

class SkyRenderer {
public:
	SkyRenderer(Shader* shader, const glm::mat4& projectionMatrix);
	~SkyRenderer() { delete m_Shader; }

	void render() const;

private:
	Shader* m_Shader;
};