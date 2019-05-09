#pragma once

#include "RawModel.h"
#include "../textures/CubeMap.h"

class CubeMapModel {
public:
	CubeMapModel(RawModel* rawModel, CubeMap* cubeMap) : m_RawModel(rawModel), m_CubeMap(cubeMap) {}
	inline RawModel* getRawModel() const { return m_RawModel; }
	inline CubeMap* getCubeMap() const { return m_CubeMap; }
	~CubeMapModel();

private:
	RawModel* m_RawModel;
	CubeMap* m_CubeMap;
};