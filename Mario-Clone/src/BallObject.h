#pragma once
#include "GameObject.h"

class BallObject : public GameObject {
public:
	float m_Radius;
	bool m_Stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture sprite);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};