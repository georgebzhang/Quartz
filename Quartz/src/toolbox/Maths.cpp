#include "Maths.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4* Maths::createTransformationMatrix(const glm::vec3* translation, const glm::vec3* rotation, const glm::vec3* scale) {
	glm::mat4* matrix = new glm::mat4(1.0f);
	*matrix = glm::translate(*matrix, *translation);
	*matrix = glm::rotate(*matrix, glm::radians(rotation->x), glm::vec3(1.0f, 0.0f, 0.0f));
	*matrix = glm::rotate(*matrix, glm::radians(rotation->y), glm::vec3(0.0f, 1.0f, 0.0f));
	*matrix = glm::rotate(*matrix, glm::radians(rotation->z), glm::vec3(0.0f, 0.0f, 1.0f));
	*matrix = glm::scale(*matrix, *scale);
	return matrix;
}
