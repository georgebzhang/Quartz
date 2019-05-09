#include "Maths.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Maths::createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) {
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, scale);
	return matrix;
}

glm::mat4 Maths::createViewMatrix(const Camera* camera) {
	glm::mat4 matrix(1.0f);
	matrix = glm::rotate(matrix, glm::radians(camera->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(camera->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	//matrix = glm::rotate(matrix, glm::radians(camera->getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, -camera->getPosition());
	return matrix;
}

float Maths::randFloat() {
	return (float)rand() / RAND_MAX;
}

int Maths::randSign() {
	return rand() % 2 ? 1 : -1;
}
