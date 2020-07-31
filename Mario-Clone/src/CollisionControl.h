#pragma once
#include "GameObject.h"
#include "BallObject.h"
#include <glm/glm.hpp>
#include <tuple>

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class CollisionControl {
public:
	static Collision CheckCollisions(BallObject& one, GameObject& two);

	static Direction VectorDirection(glm::vec2 target);
};