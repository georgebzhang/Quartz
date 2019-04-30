#pragma once

#include "../errors/ErrorHandler.h"
#include "../shaders/Shader.h"

#include "stb_image\stb_image.h"

#include <string>

class Texture {
public:
	Texture(const std::string& filePath);
	~Texture() { GLCall(glDeleteTextures(1, &m_ID)); }

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline float getAmbientReflectionConstant() const { return m_ka; }
	inline float getDiffuseReflectionConstant() const { return m_kd; }
	inline float getSpecularReflectionConstant() const { return m_ks; }
	inline float getShininessConstant() const { return m_p; }

	inline void setAmbientReflectionConstant(float ka) { m_ka = ka; }
	inline void setDiffuseReflectionConstant(float kd) { m_kd = kd; }
	inline void setSpecularReflectionConstant(float ks) { m_ks = ks; }
	inline void setShininessConstant(float p) { m_p = p; }

	void setConstants(float ka, float kd, float ks, float p);

	void loadUniforms(Shader* shader) const;

private:
	unsigned int m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

	float m_ka = 0.2; // ambient reflection constant
	float m_kd = 0.5; // diffuse reflection constant
	float m_ks = 10; // specular reflection constant
	float m_p = 100; // shininess constant
};