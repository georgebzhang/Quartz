#pragma once

class RawModel {
public:
	RawModel(int vaoID, int vertexCount);
	int getVAOID();
	int getVertexCount();

private:
	int vaoID;
	int vertexCount;
};