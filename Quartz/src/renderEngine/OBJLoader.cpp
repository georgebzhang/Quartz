#include "OBJLoader.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "glm/glm.hpp"

RawModel OBJLoader::loadOBJModel(const std::string & filePath, Loader* loader) {
	std::ifstream stream(filePath);
	std::string line;

	std::vector<glm::vec3> v_Positions;
	std::vector<glm::vec2> v_TexCoords;
	std::vector<glm::vec3> v_Normals;
	std::vector<unsigned int> v_Indices;

	float* positions = nullptr;
	float* texCoords = nullptr;
	float* normals = nullptr;
	unsigned int* indices = nullptr;

	while (std::getline(stream, line)) {
		std::stringstream split(line);
		std::vector<std::string> tokens;
		for (std::string each; std::getline(split, each, ' '); tokens.push_back(each));

		if (line.find("v ") != std::string::npos) {
			v_Positions.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		} else if (line.find("vt ") != std::string::npos) {
			v_TexCoords.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
		} else if (line.find("vn ") != std::string::npos) {
			v_Normals.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		} else if (line.find("f ") != std::string::npos) {
			texCoords = new float[v_Positions.size() * 2];
			normals = new float[v_Positions.size() * 3];
			break;
		}
	}

	while (std::getline(stream, line)) {
		if (line.find("f ") != std::string::npos) {
			std::stringstream split(line);
			std::vector<std::string> tokens;
			for (std::string each; std::getline(split, each, '/'); tokens.push_back(each));


		}
	}
}
