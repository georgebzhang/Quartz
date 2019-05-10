#include "Player.h"
#include "../renderEngine/DisplayManager.h"

const float Player::RUN_SPEED = 20;
const float Player::TURN_SPEED = 160;
const float Player::GRAVITY = -50;
const float Player::JUMP_SPEED = 30;
const float Player::TERRAIN_HEIGHT = 0;

void Player::run(bool forward) {
	m_HorizSpeed = RUN_SPEED;
	if (!forward) m_HorizSpeed *= -1;
}

void Player::turn(bool forward) {
	m_RotateSpeed = TURN_SPEED;
	if (!forward) m_RotateSpeed *= -1;
}

void Player::jump() {
	if (!m_InAir) {
		m_VertSpeed = JUMP_SPEED;
		m_InAir = true;
	}
}

void Player::move(float frameDuration) {
	// turn
	rotate(glm::vec3(0, m_RotateSpeed * frameDuration, 0));

	// run
	float distance = m_HorizSpeed * frameDuration;
	float dx = distance * sin(glm::radians(getRotation().y));
	float dz = distance * cos(glm::radians(getRotation().y));
	translate(glm::vec3(dx, 0, dz));

	// jump
	m_VertSpeed += GRAVITY * frameDuration;
	translate(glm::vec3(0, m_VertSpeed * frameDuration, 0));

	if (getPosition().y < TERRAIN_HEIGHT) {
		setPositionY(TERRAIN_HEIGHT);
		m_VertSpeed = 0;
		m_InAir = false;
	}
}

