#include "Texture.h"

Texture::Texture(const std::string & filePath) : m_ID(0), m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {
	stbi_set_flip_vertically_on_load(0); // flips texture vertically if 1
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4 for RGBA
	//std::cout << m_LocalBuffer << std::endl;
	//std::cout << m_Width << " " << m_Height << " " << m_BPP << std::endl;
	//std::cin.get();
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID)); // bind texture

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // minification filter
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // magnification filter
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer)); // 0: not multi-level texture, RGBA8: 8 bits per channel
	GLCall(glBindTexture(GL_TEXTURE_2D, 0)); // unbind texture

	if (m_LocalBuffer) // if m_LocalBuffer contains data
		stbi_image_free(m_LocalBuffer);
}

void Texture::bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::setConstants(float ka, float kd, float ks, float p) {
	setAmbientReflectionConstant(ka);
	setDiffuseReflectionConstant(kd);
	setSpecularReflectionConstant(ks);
	setShininessConstant(p);
}

void Texture::loadUniforms(Shader* shader) const {
	shader->setUniform1f("u_Has2DMesh", m_Has2DMesh);
	shader->setUniform1f("u_ka", m_ka);
	shader->setUniform1f("u_kd", m_kd);
	shader->setUniform1f("u_ks", m_ks);
	shader->setUniform1f("u_p", m_p);
}
