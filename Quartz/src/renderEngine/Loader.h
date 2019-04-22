#pragma once

#include "RawModel.h"

#include <vector>

class Loader {
public:
	RawModel loadToVAO(float* positions, int p_count, int* indices, int i_count);
	void cleanUp();

private:
	std::vector<unsigned int> vaoIDs;
	std::vector<unsigned int> vboIDs;

	unsigned int createVAO();
	void storeDataInAttributeList(int attributeNumber, float* data, int count);
	void bindIndicesBuffer(int* indices, int count);
	void unbindVAO();
};