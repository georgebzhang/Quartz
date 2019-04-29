#pragma once

#include "stb_image\stb_image.h"

#include <string>

class Texture {
public:
	Texture(const std::string& filePath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:
	unsigned int m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};