#pragma once

#include "glm/glm.hpp"

class Maths {
public:
	static glm::mat4 createTransformationMatrix(const glm::vec3 translation, const glm::vec3 rotation, const glm::vec3 scale);

private:

};