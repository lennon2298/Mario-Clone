#include "BallObject.h"

BallObject::BallObject()
	: GameObject(), m_Radius(12.5f), m_Stuck(true)
{
}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture sprite)
	:GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), m_Radius(radius), m_Stuck(true)
{
	
}

glm::vec2 BallObject::Move(float dt, unsigned int window_width)
{
	if (!m_Stuck)
	{
		// move the ball
		this->m_Position += this->m_Velocity * dt;
		// check if outside window bounds; if so, reverse velocity and restore at correct position
		if (this->m_Position.x <= 0.0f)
		{
			this->m_Velocity.x = -this->m_Velocity.x;
			this->m_Position.x = 0.0f;
		}
		else if (this->m_Position.x + this->m_Size.x >= window_width)
		{
			this->m_Velocity.x = -this->m_Velocity.x;
			this->m_Position.x = window_width - this->m_Size.x;
		}
		if (this->m_Position.y <= 0.0f)
		{
			this->m_Velocity.y = -this->m_Velocity.y;
			this->m_Position.y = 0.0f;
		}
	}
	return m_Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	m_Position = position;
	m_Velocity = velocity;
	m_Stuck = true;
}
