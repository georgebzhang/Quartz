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
	inline static float toRadians(float degrees) { return degrees * M_PI / 180.0f; }
	static float toDegrees(float radians) { return radians * 180.0f / M_PI; }

private:

};