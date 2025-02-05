#include "game_level.h"

#include <iostream>
#include <fstream>
#include <sstream>

void GameLevel::Load(const char* file, unsigned int tileSize) {
	this->Tiles.clear();

	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<GameObject> tileData;

	if (fstream) {
		std::getline(fstream, line);
		std::istringstream ss(line);
		// Here is where we get the number of tiles
		unsigned int w, h;
		ss >> w >> h;

		this->W = w * tileSize;
		this->H = h * tileSize;

		while (std::getline(fstream, line)) {
			std::istringstream ss(line);

			GameObject go;

			std::string str;
			ss >> str;
			go.spr = ResourceManager::GetTexture2D(str);
			
			ss >> go.pos.x >> go.pos.y;
			ss >> go.size.x >> go.size.y;

			go.pos.x	*= tileSize;
			go.pos.y	*= tileSize;
			go.size.x	*= tileSize;
			go.size.y	*= tileSize;

			for (int i = 0; i < 4; i++) {
				int temp;
				ss >> temp;
				go.coll[i] = (temp != 0);
			}

			for (int i = 0; i < 4; i++) {
				int temp;
				ss >> temp;
				go.port[i] = (temp != 0);
			}

			this->Tiles.push_back(go);
		}
	}
}

void GameLevel::Draw(SpriteRenderer &renderer) {
	for (GameObject &tile : this->Tiles)
		tile.Draw(renderer);
}
