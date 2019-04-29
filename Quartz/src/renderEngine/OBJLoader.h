#pragma once

#include "../models/RawModel.h"
#include "Loader.h"

class OBJLoader {
public:
	static RawModel loadOBJModel(const std::string& filePath, Loader* loader);

private:
	static void processVertex();

};