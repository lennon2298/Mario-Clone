#include "Game.h"

SpriteRenderer *spriteRenderer;

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(60.0f, -150.0f);
const float BALL_RADIUS = 12.5f;

GameObject *Player;
BallObject* Ball;

bool collision;
int count = 10;

//bool checkCollisions(GameObject& one, GameObject& two);

Game::Game(unsigned int width, unsigned int height)
	:m_State(GameState::GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height), level(0)
{
}

Game::~Game()
{
}

void Game::Init()
{
	(void)ResourceManager::LoadShader("./Resources/Shaders/TryOutVert.glsl", "./Resources/Shaders/TryOutFrag.glsl", "TryOut");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width),static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("TryOut").Bind();
	ResourceManager::GetShader("TryOut").GetUniform1i("u_Texture", 0);
	ResourceManager::GetShader("TryOut").GetUniformMat4f("u_Projection", projection);

	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("TryOut"));

	(void)ResourceManager::LoadTexture("./Resources/Textures/container2.png", true, "pepe");
	(void)ResourceManager::LoadTexture("./Resources/Textures/paddle.png", true, "player");
	(void)ResourceManager::LoadTexture("./Resources/Textures/block.png", true, "block");
	(void)ResourceManager::LoadTexture("./Resources/Textures/ball.png", true, "ball");
	(void)ResourceManager::LoadTexture("./Resources/Textures/block_solid.png", true, "block_solid");

	GameLevel one; one.Load("./Resources/levels/one.lvl", this->m_Width, this->m_Height / 2);
	GameLevel two; two.Load("./Resources/levels/two.lvl", this->m_Width, this->m_Height / 2);
	GameLevel three; three.Load("./Resources/levels/three.lvl", this->m_Width, this->m_Height / 2);
	GameLevel four; four.Load("./Resources/levels/four.lvl", this->m_Width, this->m_Height / 2);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->level = 0;

	glm::vec2 playerPos = glm::vec2( this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->m_Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));
}

void Game::ProcessInput(float dt)
{
	if (this->m_State == GameState::GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (m_Keys[GLFW_KEY_A] || m_Keys[GLFW_KEY_LEFT])
		{
			if (Player->GetPosition() >= 0.0f) {
				Player->UpdateVelocity(-velocity);
				if (Ball->m_Stuck) {
					Ball->UpdateVelocity(-velocity);
				}
			}
		}
		if (m_Keys[GLFW_KEY_D] || m_Keys[GLFW_KEY_RIGHT])
		{
			if (Player->GetPosition() <= this->m_Width - Player->GetSize()) {
				Player->UpdateVelocity(velocity);
				if (Ball->m_Stuck) {
					Ball->UpdateVelocity(velocity);
				}
			}
		}
		if (m_Keys[GLFW_KEY_SPACE])
		{
			Ball->m_Stuck = false;
		}
	}
}

void Game::Render()
{
	if (this->m_State == GameState::GAME_ACTIVE)
	{
		// draw background
		spriteRenderer->DrawSprite(ResourceManager::GetTexture("pepe"),
			glm::vec2(0.0f, 0.0f), glm::vec2(this->m_Width, this->m_Height), 0.0f);
		// draw level
		//this->Levels[this->level].Draw(*spriteRenderer);
		Levels[this->level].DrawInstanced(*spriteRenderer);
		Player->Draw(*spriteRenderer);
		Ball->Draw(*spriteRenderer);
	}
}

void Game::Update(float dt)
{
	Ball->Move(dt, this->m_Width);
	//DoCollisions();
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
	if (Ball->m_Position.y > m_Height) {
		ResetPlayer();
	}
}

bool Game::DoCollisions()
{
	bool collided = false;
	for (GameObject& box : Levels[level].m_Bricks) {
		if (!box.IsDestroyed()) {
			Collision collision = CollisionControl::CheckCollisions(*Ball, box);
			//std::cout << glm::distance(Ball->m_Position, box.m_Position) << std::endl;
			if (std::get<0>(collision)) {
				collided = true;
				if (!box.IsSolid()) {
					box.Destroy();
					auto pos = std::find_if(Levels[this->level].translationsSolid.begin(), Levels[this->level].translationsSolid.end(), [&](const glm::vec4& obj) {
						return obj.x == box.m_Position.x && obj.y == box.m_Position.y;
						});
					if(pos != Levels[level].translationsSolid.end())
						Levels[this->level].translationsSolid.erase(pos);
				}
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vec = std::get<2>(collision);
				if (dir == Direction::LEFT || dir == Direction::RIGHT) {
					Ball->m_Velocity.x = -Ball->m_Velocity.x;

					float penetration = Ball->m_Radius - std::abs(diff_vec.x);
					if (dir == Direction::LEFT) {
						Ball->m_Position.x += penetration;
					}
					else {
						Ball->m_Position.x -= penetration;
					}
				}
				else {
					Ball->m_Velocity.y = -Ball->m_Velocity.y;

					float penetration = Ball->m_Radius - std::abs(diff_vec.y);
					if (dir == Direction::UP) {
						Ball->m_Position.y += penetration;
					}
					else {
						Ball->m_Position.y -= penetration;
					}
				}
			}
		}

		Collision result = CollisionControl::CheckCollisions(*Ball, *Player);
		if (!Ball->m_Stuck && std::get<0>(result)) {
			float centerBoard = Player->m_Position.x + Player->m_Size.x / 2.0f;
			float distance = (Ball->m_Position.x + Ball->m_Radius) - centerBoard;
			float percentage = distance / (Player->m_Size.x / 2.0f);
			// then move accordingly
			float strength = 2.0f;
			glm::vec2 oldVelocity = Ball->m_Velocity;
			Ball->m_Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			Ball->m_Velocity.y = -1 * abs(Ball->m_Velocity.y);
			Ball->m_Velocity = glm::normalize(Ball->m_Velocity) * glm::length(oldVelocity);
			collided = true;
		}
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
	Player->m_Position = glm::vec2(this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->m_Height - PLAYER_SIZE.y);
	Ball->Reset(Player->m_Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}
