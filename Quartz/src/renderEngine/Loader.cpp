#include "Loader.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"

#include <GL/glew.h>

//RawModel Loader::loadToVAO(float* positions, int p_count, int* indices, int i_count) {
RawModel* Loader::loadToVAO(float* positions, int p_count, float* texCoords, int t_count, unsigned int* indices, int i_count) {
	VertexArray* va = new VertexArray();
	VertexBuffer* vb0 = new VertexBuffer(positions, p_count * sizeof(float));
	va->addBuffer(vb0, 0, 3);
	VertexBuffer* vb1 = new VertexBuffer(texCoords, t_count * sizeof(float));
	va->addBuffer(vb1, 1, 2);
	IndexBuffer* ib = new IndexBuffer(indices, i_count);
	return new RawModel(va, ib);
}

//Texture Loader::loadTexture(std::string filePath) {
//	return Texture(filePath);
//}

//unsigned int Loader::createVAO() {
//	unsigned int vaoID;
//	glGenVertexArrays(1, &vaoID);
//	//vaoIDs.emplace_back(vaoID);
//	glBindVertexArray(vaoID);
//	return vaoID;
//}
//
//void Loader::storeDataInAttributeList(int attributeNumber, int single_count, float* data, int count) {
//	unsigned int vboID;
//	glGenBuffers(1, &vboID);
//	//vboIDs.emplace_back(vboID);
//	glBindBuffer(GL_ARRAY_BUFFER, vboID);
//	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
//	glVertexAttribPointer(attributeNumber, single_count, GL_FLOAT, false, 0, (const void*) 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void Loader::unbindVAO() {
//	glBindVertexArray(0);
//}
//
//void Loader::bindIndicesBuffer(unsigned int* indices, int count) {
//	unsigned int vboID;
//	glGenBuffers(1, &vboID);
//	//vboIDs.emplace_back(vboID);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, GL_STATIC_DRAW);
//}

//void Loader::cleanUp() {
//	for (unsigned int id : vaoIDs) {
//		glDeleteVertexArrays(1, &id);
//	}
//	for (unsigned int id : vboIDs) {
//		glDeleteVertexArrays(1, &id);
//	}
//}