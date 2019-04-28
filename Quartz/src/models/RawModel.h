#pragma once

class RawModel {
public:
	RawModel(int vaoID, int vertexCount);
	int getVAOID();
	int getVertexCount();
	~RawModel();

private:
	int vaoID;
	int vertexCount;
};