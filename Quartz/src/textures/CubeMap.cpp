#include "CubeMap.h"

CubeMap::CubeMap() {
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));
	int width, height, nrChannels;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// not necessary?
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < m_Faces.size(); i++) {
		unsigned char *data = stbi_load(m_Faces[i].c_str(), &width, &height, &nrChannels, 4);
		//std::cout << width << ", " << height << std::endl;
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else {
			std::cout << "Cubemap texture failed to load at path: " << m_Faces[i].c_str() << std::endl;
			stbi_image_free(data);
		}
	}

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void CubeMap::bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));
}

void CubeMap::unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
