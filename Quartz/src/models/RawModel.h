#pragma once

class RawModel {
public:
	RawModel(int vaoID, int vertexCount);
	int getVAOID();
	int getVertexCount();
	~RawModel();

private:
	int m_VAOID;
	int m_VertexCount;
};