#include "game_level.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char* file, unsigned int lvlW, unsigned int lvlH) {
	this->Bricks.clear();

	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}

		if (tileData.size() > 0)
			this->init(tileData, lvlW, lvlH);
	}
}

void GameLevel::Draw(SpriteRenderer &renderer) {
	for (GameObject &tile : this->Bricks)
		if (!tile.destroyed)
			tile.Draw(renderer);
}

bool GameLevel::isComplete() {
	for (GameObject &tile : this->Bricks)
		if (!tile.solid && !tile.destroyed)
			return false;
	return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int lvlW, unsigned int lvlH) {
	unsigned int h	= tileData.size();
	unsigned int w	= tileData[0].size();

	float unit_w	= lvlW / static_cast<float>(w), unit_h = lvlH / static_cast<float>(h);

	for (unsigned int y = 0; y < h; y++) {
		for(unsigned int x = 0; x < w; x++) {
			if (tileData[y][x] == 1) {
				glm::vec2 pos(unit_w * x, unit_h * y);
				glm::vec2 size(unit_w, unit_h);
				GameObject obj(pos, size, ResourceManager::GetTexture2D("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.solid = true;
				this->Bricks.push_back(obj);
			} else if (tileData[y][x] > 1) {
				glm::vec3 color = glm::vec3(1.0f);
				if (tileData[y][x] == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unit_w * x, unit_h * y);
				glm::vec2 size(unit_w, unit_h);
				this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture2D("block"), color));
			}
		}
	}
}
