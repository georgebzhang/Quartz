#include "OBJLoader.h"
#include "../toolbox/Maths.h"

#include <fstream>
#include <sstream>
#include <iostream>

RawModel* OBJLoader::loadOBJModel(const std::string & filePath, Loader* loader) {
	std::ifstream stream(filePath);
	std::string line;

	std::vector<glm::vec3> v_Positions;
	std::vector<glm::vec2> v_TexCoords;
	std::vector<glm::vec3> v_Normals;
	std::vector<unsigned int> v_Indices;

	int p_count, t_count, n_count, i_count;

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
			t_count = v_Positions.size() * 2;
			texCoords = new float[t_count];
			n_count = v_Positions.size() * 3;
			normals = new float[n_count];
			break;
		}
	}

	while (!line.empty()) {
		if (line.find("f ") != std::string::npos) {
			std::stringstream split(line);
			std::vector<std::string> triangleTokens;
			for (std::string each; std::getline(split, each, ' '); triangleTokens.push_back(each));
			triangleTokens.erase(triangleTokens.begin());
			for (std::string vertex : triangleTokens) {
				std::stringstream vertexSplit(vertex);
				std::vector<std::string> vertexTokens;
				for (std::string each; std::getline(vertexSplit, each, '/'); vertexTokens.push_back(each));
				processVertex(vertexTokens, v_TexCoords, v_Normals, v_Indices, texCoords, normals);
			}

		}
		std::getline(stream, line);
	}

	p_count = v_Positions.size() * 3;
	positions = new float[p_count];
	i_count = v_Indices.size();
	indices = new unsigned int[i_count];

	int i = 0;
	for (glm::vec3 position : v_Positions) {
		positions[i++] = position.x;
		positions[i++] = position.y;
		positions[i++] = position.z;
	}

	for (int i = 0; i < v_Indices.size(); ++i) {
		indices[i] = v_Indices[i];
	}

	//float offset = 0.1;
	//for (int i = 0; i < p_count; ++i) {
	//	positions[i] += Maths::randSign() * offset;
	//}

	return loader->loadToVAO(positions, p_count, texCoords, t_count, normals, n_count, indices, i_count);
}

void OBJLoader::processVertex(const std::vector<std::string>& vertexTokens, const std::vector<glm::vec2>& v_TexCoords, const std::vector<glm::vec3>& v_Normals, std::vector<unsigned int>& v_Indices, float* texCoords, float* normals) {
	int vertexIndex = std::stoi(vertexTokens[0]) - 1;
	v_Indices.push_back(vertexIndex);
	glm::vec2 texCoord = v_TexCoords[std::stoi(vertexTokens[1]) - 1];
	texCoords[vertexIndex * 2] = texCoord.x;
	texCoords[vertexIndex * 2 + 1] = 1 - texCoord.y;
	glm::vec3 normal = v_Normals [std::stoi(vertexTokens[2]) - 1];
	normals[vertexIndex * 3] = normal.x;
	normals[vertexIndex * 3 + 1] = normal.y;
	normals[vertexIndex * 3 + 2] = normal.z;
}

Buffer* OBJLoader::loadOBJModel2(const std::string & filePath, Loader* loader) {
	std::ifstream stream(filePath);
	std::string line;

	std::vector<glm::vec3> v_Positions;
	std::vector<glm::vec2> v_TexCoords;
	std::vector<glm::vec3> v_Normals;
	std::vector<unsigned int> v_Indices;

	int p_count, t_count, n_count, i_count;

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
		}
		else if (line.find("vt ") != std::string::npos) {
			v_TexCoords.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
		}
		else if (line.find("vn ") != std::string::npos) {
			v_Normals.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		}
		else if (line.find("f ") != std::string::npos) {
			t_count = v_Positions.size() * 2;
			texCoords = new float[t_count];
			n_count = v_Positions.size() * 3;
			normals = new float[n_count];
			break;
		}
	}

	while (!line.empty()) {
		if (line.find("f ") != std::string::npos) {
			std::stringstream split(line);
			std::vector<std::string> triangleTokens;
			for (std::string each; std::getline(split, each, ' '); triangleTokens.push_back(each));
			triangleTokens.erase(triangleTokens.begin());
			for (std::string vertex : triangleTokens) {
				std::stringstream vertexSplit(vertex);
				std::vector<std::string> vertexTokens;
				for (std::string each; std::getline(vertexSplit, each, '/'); vertexTokens.push_back(each));
				processVertex(vertexTokens, v_TexCoords, v_Normals, v_Indices, texCoords, normals);
			}

		}
		std::getline(stream, line);
	}

	p_count = v_Positions.size() * 3;
	positions = new float[p_count];
	i_count = v_Indices.size();
	indices = new unsigned int[i_count];

	int i = 0;
	for (glm::vec3 position : v_Positions) {
		positions[i++] = position.x;
		positions[i++] = position.y;
		positions[i++] = position.z;
	}

	for (int i = 0; i < v_Indices.size(); ++i) {
		indices[i] = v_Indices[i];
	}

	return new Buffer(positions, p_count, texCoords, t_count, normals, n_count, indices, i_count);
}