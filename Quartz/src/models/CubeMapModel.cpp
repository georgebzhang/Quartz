#include "CubeMapModel.h"

CubeMapModel::~CubeMapModel() {
	delete m_RawModel;
	delete m_CubeMap;
}
