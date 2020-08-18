#include "Game.h"

SpriteRenderer *spriteRenderer;

const glm::vec2 PLAYER_SIZE(30.0f, 80.0f);
const float PLAYER_VELOCITY(250.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(60.0f, -150.0f);
const float BALL_RADIUS = 12.5f;

glm::vec2 bgPos = glm::vec2(0.0f, 0.0f);

GameObject *Player;
BallObject* Ball;
GameObject* BackGround;

bool collision;
int count = 10;

Game::Game(unsigned int width, unsigned int height)
	:m_State(GameState::GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height), level(0), m_Projection(glm::mat4(1.0f)), m_WindowLower(0.0f), m_WindowUpper(width)
{
}

Game::~Game()
{
}

void Game::Init()
{
	(void)ResourceManager::LoadShader("./Resources/Shaders/TryOutVert.glsl", "./Resources/Shaders/TryOutFrag.glsl", "TryOut");
	m_Projection = glm::ortho(0.0f, static_cast<float>(m_Width),static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, 0.0f));
	ResourceManager::GetShader("TryOut").Bind();
	ResourceManager::GetShader("TryOut").GetUniformMat4f("u_View", view);
	ResourceManager::GetShader("TryOut").GetUniform1i("u_Texture", 0);
	ResourceManager::GetShader("TryOut").GetUniformMat4f("u_Projection", m_Projection);

	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("TryOut"));

	(void)ResourceManager::LoadTexture("./Resources/Textures/container2.png", true, "pepe");
	(void)ResourceManager::LoadTexture("./Resources/Textures/mario.png", true, "player");
	(void)ResourceManager::LoadTexture("./Resources/Textures/solidBlock.png", true, "block");
	(void)ResourceManager::LoadTexture("./Resources/Textures/ball.png", true, "ball");
	(void)ResourceManager::LoadTexture("./Resources/Textures/baseWall.png", true, "block_solid");
	(void)ResourceManager::LoadTexture("./Resources/Textures/brickWall.png", true, "block_brick");

	GameLevel one; one.Load("./Resources/levels/one - copy.lvl", this->m_Width, this->m_Height / 2);
	GameLevel two; two.Load("./Resources/levels/two.lvl", this->m_Width, this->m_Height / 2);
	GameLevel three; three.Load("./Resources/levels/three.lvl", this->m_Width, this->m_Height / 2);
	GameLevel four; four.Load("./Resources/levels/four.lvl", this->m_Width, this->m_Height / 2);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->level = 0;

	glm::vec2 playerPos = glm::vec2( this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->m_Height - (PLAYER_SIZE.y + 86.0f));
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));
	BackGround = new GameObject(bgPos, glm::vec2(this->m_Width, this->m_Height), ResourceManager::GetTexture("pepe"));
}

void Game::ProcessInput(float dt)
{
	float xPos = this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f;
	if (this->m_State == GameState::GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (m_Keys[GLFW_KEY_A] || m_Keys[GLFW_KEY_LEFT])
		{
			if (Player->GetPosition() >= m_WindowLower && Player->m_MovableBack) {
				Player->m_MovableForward = true;
				Player->UpdateVelocity(-velocity);
				m_WindowUpper = m_WindowLower + static_cast<float>(m_Width);
				glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_WindowLower, 0.0f, 0.0f));
				ResourceManager::GetShader("TryOut").GetUniformMat4f("u_View", view);
				if (Ball->m_Stuck) {
					Ball->UpdateVelocity(-velocity);
				}
			}
		}
		if (m_Keys[GLFW_KEY_D] || m_Keys[GLFW_KEY_RIGHT])
		{
			if (Player->GetPosition() <= m_WindowUpper - Player->GetSize() && Player->m_MovableForward) {
				Player->m_MovableBack = true;
				Player->UpdateVelocity(velocity);
				if (Player->m_Position.x <= m_WindowLower + xPos) {
					m_WindowUpper = m_WindowLower + static_cast<float>(m_Width);
				}
				else {
					m_WindowLower = Player->m_Position.x - xPos;
					m_WindowUpper = m_WindowLower + static_cast<float>(m_Width);
					BackGround->UpdateVelocity(velocity);
				}
				glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_WindowLower, 0.0f, 0.0f));
				ResourceManager::GetShader("TryOut").GetUniformMat4f("u_View", view);
				if (Ball->m_Stuck) {
					Ball->UpdateVelocity(velocity);
				}
			}
		}
		bgPos = BackGround->m_Position;
		if (m_Keys[GLFW_KEY_SPACE])
		{
			if (Player->m_Stuck) {
				Player->m_Stuck = false;
				Player->m_MovableBack = true;
				Player->m_MovableForward = true;
				Player->m_Velocity.y = -2500.0f;
			}
		}
	}
}

void Game::Render()
{
	if (this->m_State == GameState::GAME_ACTIVE)
	{
		// draw background
		//spriteRenderer->DrawSprite(ResourceManager::GetTexture("pepe"),bgPos, glm::vec2(this->m_Width, this->m_Height), 0.0f);
		//ddBackGround->Draw(*spriteRenderer);
		// draw level
		Levels[this->level].DrawInstanced(*spriteRenderer);
		Player->Draw(*spriteRenderer);
		//Ball->Draw(*spriteRenderer);
	}
}

void Game::Update(float dt)
{
	//Ball->Move(dt, m_WindowLower, m_WindowUpper);
	//DoCollisions();
	Player->Move(dt);
	if (!collision) {
		collision = DoCollisions();
	}
	else {
		count--;
		if (count == 0) {
			collision = false;
			count = 10;
		}
	}
	if (Player->m_Position.y > m_Height) {
		ResetPlayer();
	}
}

bool Game::DoCollisions()
{
	Player->m_Stuck = false;
	bool collided = false;
	for (GameObject& box : Levels[level].m_Bricks) {
		if (!box.IsDestroyed()) {
			Collision collision = CollisionControl::CheckCollisions(*Player, box);
			if (std::get<0>(collision)) {
				collided = true;
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vec = std::get<2>(collision);
				if (dir == Direction::LEFT) {
					Player->m_Velocity.x = 0;
					Player->m_MovableBack = false;
				}
				else if (dir == Direction::RIGHT) {
					Player->m_Velocity.x = 0;
					Player->m_MovableForward = false;
				}
				else {
					Player->m_Velocity.y = 0;

					if (dir == Direction::UP) {
						Player->m_Stuck = true;
						Player->m_Velocity.y = 0;
					}
				}
				if (!box.IsSolid()) {
					auto pos = std::find_if(Levels[this->level].translationsSolid.begin(), Levels[this->level].translationsSolid.end(), [&](const glm::vec4& obj) {
						return obj.x == box.m_Position.x && obj.y == box.m_Position.y;
						});
					if (pos != Levels[level].translationsSolid.end() && dir == Direction::DOWN) {
						Levels[this->level].translationsSolid.erase(pos);
						box.Destroy();
					}
				}
			}
		}

		//Collision result = CollisionControl::CheckCollisions(*Ball, *Player);
		//if (!Ball->m_Stuck && std::get<0>(result)) {
		//	float centerBoard = Player->m_Position.x + Player->m_Size.x / 2.0f;
		//	float distance = (Ball->m_Position.x + Ball->m_Radius) - centerBoard;
		//	float percentage = distance / (Player->m_Size.x / 2.0f);
		//	// then move accordingly
		//	float strength = 2.0f;
		//	glm::vec2 oldVelocity = Ball->m_Velocity;
		//	Ball->m_Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//	Ball->m_Velocity.y = -1 * abs(Ball->m_Velocity.y);
		//	Ball->m_Velocity = glm::normalize(Ball->m_Velocity) * glm::length(oldVelocity);
		//	collided = true;
		//}
	}
	return collided;
}

void Game::SetState(GameState state)
{
	m_State = state;
}

void Game::SetKeyPress(int key)
{
	m_Keys[key] = true;
}

void Game::SetKeyRelease(int key)
{
	m_Keys[key] = false;
}

GameState Game::GetState()
{
	return m_State;
}

void Game::ResetLevel()
{
	if (this->level == 0)
		this->Levels[0].Load("levels/one.lvl", this->m_Width, this->m_Height / 2);
	else if (this->level == 1)
		this->Levels[1].Load("levels/two.lvl", this->m_Width, this->m_Height / 2);
	else if (this->level == 2)
		this->Levels[2].Load("levels/three.lvl", this->m_Width, this->m_Height / 2);
	else if (this->level == 3)
		this->Levels[3].Load("levels/four.lvl", this->m_Width, this->m_Height / 2);
}

void Game::ResetPlayer()
{
	// reset player/ball stats
	Player->m_Size = PLAYER_SIZE;
	Player->m_Position = glm::vec2(m_WindowLower + (this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f), this->m_Height - (PLAYER_SIZE.y + 86.0f));
	BackGround->m_Position = bgPos;
}
