#pragma once

#include "../entities/Camera.h"

#include "glm/glm.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

class Maths {
public:
	static glm::mat4 createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	static glm::mat4 createViewMatrix(const Camera* camera);
	static float randFloat();
	static int randSign();

private:

};