#include "Entity.h"

Entity::~Entity() {
	delete m_TexturedModel;
}
