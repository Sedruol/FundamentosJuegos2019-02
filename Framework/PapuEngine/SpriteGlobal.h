#pragma once
#include <glm\glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
//cree
const float GLOBAL_WIDTH = 60.0f;
class SpriteGlobal
{
private:
	glm::vec2 position;
	char type;
	Color color;
public:
	glm::vec2 getPosition() const {
		return position;
	}
	void init(glm::vec2 _position, char _type);
	void draw(SpriteBacth& spritebatch);
	SpriteGlobal();
	~SpriteGlobal();
};

