#pragma once

#include "../models/RawModel.h"
#include "../textures/Texture.h"

#include <vector>

class Loader {
public:
	//RawModel loadToVAO(float* positions, int p_count, int* indices, int i_count);
	RawModel loadToVAO(float* positions, int p_count, float* texCoords, int t_count, unsigned int* indices, int i_count);
	//Texture loadTexture(std::string filePath);
	//void cleanUp();

private:
	//std::vector<unsigned int> vaoIDs;
	//std::vector<unsigned int> vboIDs;
	//std::vector<unsigned int> textureIDs;

	unsigned int createVAO();
	void storeDataInAttributeList(int attributeNumber, int single_count, float* data, int count);
	void bindIndicesBuffer(unsigned int* indices, int count);
	void unbindVAO();
};