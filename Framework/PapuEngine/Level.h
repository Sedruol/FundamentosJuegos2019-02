#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"
//movi aqui
using namespace std;

const int TILE_WIDTH = 64;


class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
public:
	Level(const string& filename);
	glm::vec2 playerPosition;
	vector<glm::vec2> zombiePosition;
	glm::vec2 getPlayerPosition()const {
		return playerPosition;
	}
	vector<glm::vec2> getZombiesPosition() const {
		return zombiePosition;
	}////
	vector<string> getLevelData()const {
		return levelData;
	}
	int getWidth() const {
		return TILE_WIDTH;
	}
	int getHeight() const {
		return TILE_WIDTH;
	}

	int getNumHumans()const {
		return numHumans;
	}///
	void draw();
	SpriteBacth spritebatch;
	~Level();
};

