#include "Entity.h"

Entity::~Entity() {
	delete m_TexturedModel;
}

void Entity::translate(const glm::vec3 translation) {
	m_Position += translation;
}

void Entity::rotate(const glm::vec3 rotation) {
	m_Rotation += rotation;
}
