#include "Loader.h"

#include <GL/glew.h>

RawModel Loader::loadToVAO(float* positions, int count) {
	unsigned int vaoID = createVAO();
	storeDataInAttributeList(0, positions, count);
	unbindVAO();
	return RawModel(vaoID, count / 3);
}

unsigned int Loader::createVAO() {
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	vaoIDs.emplace_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, float* data, int count) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vboIDs.emplace_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, (const void*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

void Loader::cleanUp() {
	for (unsigned int id : vaoIDs) {
		glDeleteVertexArrays(1, &id);
	}
	for (unsigned int id : vboIDs) {
		glDeleteVertexArrays(1, &id);
	}
}