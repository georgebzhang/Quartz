#include "Light.h"

void Light::loadUniforms(Shader* shader) const {
	shader->setUniform3fv("u_I", m_Intensity);
	shader->setUniform3fv("u_LightPosition", m_Position);
	shader->setUniform3fv("u_Ia", m_Color);
}
