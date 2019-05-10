#pragma once

#include "../models/RawModel.h"
#include "Loader.h"

#include "glm/glm.hpp"

struct Buffer {
	Buffer(float* positions, int pcount, float* texCoords, int tcount, float* normals, int ncount, unsigned* indices, int icount) : m_Positions(positions), m_Pcount(pcount), m_TexCoords(texCoords), m_Tcount(tcount), m_Normals(normals), m_Ncount(ncount), m_Indices(indices), m_Icount(icount) {}

	~Buffer() {
		delete[] m_Positions;
		delete[] m_TexCoords;
		delete[] m_Normals;
		delete[] m_Indices;
	}

	float* m_Positions;
	int m_Pcount;
	float* m_TexCoords;
	int m_Tcount;
	float* m_Normals;
	int m_Ncount;
	unsigned* m_Indices;
	int m_Icount;
};

class OBJLoader {
public:
	static RawModel* loadOBJModel(const std::string& filePath, Loader* loader);
	static Buffer* loadOBJModel2(const std::string& filePath, Loader* loader);
	

private:
	static void processVertex(const std::vector<std::string>& vertexTokens, const std::vector<glm::vec2>& v_TexCoords, const std::vector<glm::vec3>& v_Normals, std::vector<unsigned int>& v_Indices, float* texCoords, float* normals);

};