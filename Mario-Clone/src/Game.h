#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <vector>
#include <algorithm>

#include "SpriteRenderer.h"
#include "ErrorHandling.h"
#include "ResourceManager.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "CollisionControl.h"

enum class GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
private:
	unsigned int m_Width, m_Height;
	bool m_Keys[1024];
	GameState m_State;
	std::vector<GameLevel> Levels;
	unsigned int level;
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();

	void ProcessInput(float dt);
	void Render();
	void Update(float dt);

	bool DoCollisions();

	void SetState(GameState state);
	void SetKeyPress(int key);
	void SetKeyRelease(int key);
	GameState GetState();
	void ResetPlayer();
	void ResetLevel();

};
