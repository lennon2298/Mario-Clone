#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject {
public:
	glm::vec2   m_Position, m_Size, m_Velocity;
	glm::vec3   m_Color;
	float       m_Rotation;
	bool        m_IsSolid;
	bool        m_Destroyed;
	unsigned int m_iterator;

	Texture m_Sprite;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, unsigned int iterator = 0, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// draw sprite
	virtual void Draw(SpriteRenderer& renderer);

	void SetSolid();
	bool IsSolid();
	bool IsDestroyed();
	void Destroy();
	unsigned int GetIterator();

	float GetPosition();
	void UpdateVelocity(float x);

	float GetSize();
};
