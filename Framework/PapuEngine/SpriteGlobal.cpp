#include "SpriteGlobal.h"
#include "ResourceManager.h"

//cree
void SpriteGlobal::init(glm::vec2 _position, char _type)
{
	type = _type;
	position = _position;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
}

void SpriteGlobal::draw(SpriteBacth & spritebatch)
{
	static int textureID;
	switch (type)
	{
	case 'A':
		textureID = ResourceManager::getTexture("Textures/padoru_cc.png").id;
		break;
	case 'B':
		textureID = ResourceManager::getTexture("Textures/padoru_zero_two.png").id;
		break;
	case 'C':
		textureID = ResourceManager::getTexture("Textures/Paper_Mario_.png").id;
		break;
	case 'D':
		textureID = ResourceManager::getTexture("Textures/padoru_kurumi.png").id;
		break;
	case 'E':
		textureID = ResourceManager::getTexture("Textures/viper.png").id;
		break;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, GLOBAL_WIDTH, GLOBAL_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

SpriteGlobal::SpriteGlobal()
{
}


SpriteGlobal::~SpriteGlobal()
{
}
