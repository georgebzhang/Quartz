#pragma once

#include "../entities/Camera.h"

#include "glm/glm.hpp"

class Maths {
public:
	static glm::mat4 createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	static glm::mat4 createViewMatrix(const Camera* camera);
	static float randFloat();

private:

};