#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel {
public:
	std::vector<GameObject> m_Bricks;
	std::vector<glm::vec4> translationsSolid;
	glm::vec2 translationsOne[50];
	glm::vec2 translationsTwo[50];
	glm::vec2 translationsThree[50];
	glm::vec2 translationsFour[50];
	unsigned int solidCount = 0, oneCount = 0, twoCount = 0, threeCount = 0, fourCount = 0, iterator = 0;
	float unit_width = 0.0f, unit_height = 0.0f;

	GameLevel() {};

	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRenderer &renderer);
	void DrawInstanced(SpriteRenderer& renderer);
	bool isCompleted();

	void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};
