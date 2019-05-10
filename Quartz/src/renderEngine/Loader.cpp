#include "Loader.h"
#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"

#include <GL/glew.h>

//RawModel Loader::loadToVAO(float* positions, int p_count, int* indices, int i_count) {
RawModel* Loader::loadToVAO(float* positions, int p_count, float* texCoords, int t_count, float* normals, int n_count, unsigned int* indices, int i_count) {
	VertexArray* va = new VertexArray();
	VertexBuffer* vb0 = new VertexBuffer(positions, p_count * sizeof(float));
	va->addBuffer(vb0, 0, 3);
	VertexBuffer* vb1 = new VertexBuffer(texCoords, t_count * sizeof(float));
	va->addBuffer(vb1, 1, 2);
	VertexBuffer* vb2 = new VertexBuffer(normals, n_count * sizeof(float));
	va->addBuffer(vb2, 2, 3);
	IndexBuffer* ib = new IndexBuffer(indices, i_count);
	// delete heap-allocated arrays after glBufferData(...)
	//delete[] positions;
	//delete[] texCoords;
	//delete[] normals;
	//delete[] indices;
	return new RawModel(va, ib);
}

RawModel* Loader::loadToVAO(float* positions, int p_count) {
	VertexArray* va = new VertexArray();
	VertexBuffer* vb0 = new VertexBuffer(positions, p_count * sizeof(float));
	va->addBuffer(vb0, 0, 3);
	// delete heap-allocated arrays after glBufferData(...)
	delete[] positions;
	return new RawModel(va, nullptr);
}
