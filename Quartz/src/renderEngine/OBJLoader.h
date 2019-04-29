#pragma once

#include "../models/RawModel.h"
#include "Loader.h"

#include "glm/glm.hpp"

class OBJLoader {
public:
	static RawModel* loadOBJModel(const std::string& filePath, Loader* loader);

private:
	static void processVertex(const std::vector<std::string>& vertexTokens, const std::vector<glm::vec2>& v_TexCoords, const std::vector<glm::vec3>& v_Normals, std::vector<unsigned int>& v_Indices, float* texCoords, float* normals);

};