#pragma once

#include "../shaders/Shader.h"
#include "Player.h"

#include "glm/glm.hpp"

class Camera {
public:
	Camera(Player* player, glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f)) : m_Player(player), m_Position(position) {}
	~Camera() {}

	inline glm::vec3 getPosition() const { return m_Position; }
	inline float getPitch() const { return m_Pitch; }
	inline float getYaw() const { return m_Yaw; }
	inline float getRoll() const { return m_Roll; }

	inline void translate(const glm::vec3& translation) { m_Position += translation; }
	inline void setPosition(const glm::vec3& position) { m_Position = position; }

	void loadUniforms(Shader* shader) const;
	void loadUniforms2(Shader* shader) const;

	void updateZoom(float d);
	void updatePitch(float d);
	void updateAngle(float d);

	void move();

private:
	Player* m_Player;

	glm::vec3 m_Position;
	float m_Pitch, m_Yaw, m_Roll;

	float m_DistanceFromPlayer = 50;
	float m_AngleAroundPlayer = 0;

};