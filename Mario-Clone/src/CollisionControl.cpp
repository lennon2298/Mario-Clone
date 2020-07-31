#include "CollisionControl.h"
#include <glad/glad.h>

Collision CollisionControl::CheckCollisions(BallObject& one, GameObject& two)
{
	glm::vec2 center(one.m_Position + one.m_Radius);

	glm::vec2 aabb_half_extents(
		two.m_Size.x / 2, two.m_Size.y / 2
	);

	glm::vec2 aabb_center(
		two.m_Position.x + aabb_half_extents.x,
		two.m_Position.y + aabb_half_extents.y
	);

	glm::vec2 difference = center - aabb_center;

	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if (glm::length(difference) < one.m_Radius) {
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else {
		return std::make_tuple(false, Direction::UP, glm::vec2(0.0f, 0.0f));
	}
}

Direction CollisionControl::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
