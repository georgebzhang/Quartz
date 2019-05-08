#pragma once

#include "../models/RawModel.h"
#include "../textures/Texture.h"

#include <vector>

class Loader {
public:
	RawModel* loadToVAO(float* positions, int p_count, float* texCoords, int t_count, float* normals, int n_count, unsigned int* indices, int i_count);

	RawModel* loadToVAO(float* positions, int p_count);

private:

};