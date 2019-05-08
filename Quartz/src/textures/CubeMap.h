#pragma once

#include "../errors/ErrorHandler.h"

#include "stb_image\stb_image.h"

#include <vector>

class CubeMap {
public:
	CubeMap();
	~CubeMap();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_ID;
	std::vector<std::string> m_Faces = { "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" };

};