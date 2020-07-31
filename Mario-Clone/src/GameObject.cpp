#include "GameObject.h"

GameObject::GameObject()
	:m_Position(100.0,100.0), m_Color(0.0, 0.0, 0.0), m_Size(10.0, 10.0), m_Velocity(0.0, 0.0), m_Sprite(), m_Rotation(0.0), m_IsSolid(false), m_Destroyed(false)
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: m_Position(pos), m_Color(color), m_Size(size), m_Velocity(velocity), m_Sprite(sprite), m_Rotation(0.0), m_IsSolid(false), m_Destroyed(false)
{
}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(m_Sprite, m_Position, m_Size, m_Rotation, m_Color);
}

void GameObject::SetSolid()
{
	m_IsSolid = true;
}

bool GameObject::IsSolid()
{
	return m_IsSolid;
}

bool GameObject::IsDestroyed()
{
	return m_Destroyed;
}

void GameObject::Destroy()
{
	m_Destroyed = true;
}

float GameObject::GetPosition()
{
	return m_Position.x;
}

void GameObject::UpdateVelocity(float x)
{
	m_Position.x += x;
}

float GameObject::GetSize()
{
	return m_Size.x;
}
