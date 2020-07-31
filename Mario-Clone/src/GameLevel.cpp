#include "GameLevel.h"

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	m_Bricks.clear();

	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->Init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (GameObject& tile : this->m_Bricks)
		if (!tile.IsDestroyed())
			tile.Draw(renderer);
}

void GameLevel::DrawInstanced(SpriteRenderer& renderer)
{
	glm::vec2 size(unit_width - 1.0, unit_height);
	renderer.DrawInstanced(std::size(translationsSolid), translationsSolid[0], size, glm::vec3(0.8f, 0.8f, 0.7f));
}

bool GameLevel::isCompleted()
{
	for (GameObject& tile : this->m_Bricks)
		if (!tile.IsSolid() && !tile.IsDestroyed())
			return false;
	return true;
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	unit_width = levelWidth / static_cast<float>(width);
	unit_height = levelHeight / height;
	//unit_width = 60.0f;
	//unit_height = 30.0f;
	std::cout << unit_width << std::endl;
	std::cout << unit_height << std::endl;

	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			if (tileData[y][x] == 1)
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width - 1.0, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.SetSolid();
				this->m_Bricks.push_back(obj);
				translationsSolid.push_back(glm::vec4(pos, 0, 0));
			}
			else if(tileData[y][x] > 1) {
				glm::vec2 pos(unit_width * x, unit_height * y);

				glm::vec3 color = glm::vec3(1.0f); // original: white
				if (tileData[y][x] == 2) {
					color = glm::vec3(0.2f, 0.6f, 1.0f);
					translationsSolid.push_back(glm::vec4(pos, 1, 2));
				}
				else if (tileData[y][x] == 3) {
					color = glm::vec3(0.0f, 0.7f, 0.0f);
					translationsSolid.push_back(glm::vec4(pos, 1, 3));
				}
				else if (tileData[y][x] == 4) {
					color = glm::vec3(0.8f, 0.8f, 0.4f);
					translationsSolid.push_back(glm::vec4(pos, 1, 4));
				}
				else if (tileData[y][x] == 5) {
					color = glm::vec3(1.0f, 0.5f, 0.0f);
					translationsSolid.push_back(glm::vec4(pos, 1, 5));
				}

				glm::vec2 size(unit_width - 1, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block"), color);
				this->m_Bricks.push_back(obj);
			}
		}
	}
}
