#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Entity(texturedModel, position, rotation, scale) {}
	~Player() {}

	void run(bool forward);
	inline void stopMove() { m_HorizSpeed = 0; }
	void turn(bool forward);
	inline void stopTurn() { m_RotateSpeed = 0; }
	void jump();

	void move(float frameDuration);

private:
	static const float RUN_SPEED; // units/sec
	static const float TURN_SPEED; // deg/sec
	static const float GRAVITY;
	static const float JUMP_SPEED;
	static const float TERRAIN_HEIGHT;
	
	float m_HorizSpeed = 0;
	float m_RotateSpeed = 0;
	float m_VertSpeed = 0;
	bool m_InAir = false;
};