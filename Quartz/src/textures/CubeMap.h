#pragma once

#include "../errors/ErrorHandler.h"

#include "stb_image\stb_image.h"

#include <vector>

class CubeMap {
public:
	CubeMap();
	~CubeMap() { GLCall(glDeleteTextures(1, &m_ID)); }

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:
	unsigned int m_ID;
	//std::vector<std::string> m_Faces = { "res/textures/right.png", "res/textures/left.png", "res/textures/top.png", "res/textures/bottom.png", "res/textures/back.png", "res/textures/front.png" };
	std::vector<std::string> m_Faces = { "res/textures/Lycksele/right.jpg", "res/textures/Lycksele/left.jpg", "res/textures/Lycksele/top.jpg", "res/textures/Lycksele/bottom.jpg", "res/textures/Lycksele/back.jpg", "res/textures/Lycksele/front.jpg" };
};