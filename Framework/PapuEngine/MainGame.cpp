#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"

#include <random>
#include <ctime>
//movi aqui
using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Ella se fue :'v", _witdh, _height, 0);
	initLevel();
	initShaders();
	_spriteBacth.init();
}

void MainGame::initLevel() {
	currentLevel = 0;
	levels.push_back(new Level("Levels/level.txt"));
	player = new Player();
	player->init(0.2f, levels[currentLevel]->getPlayerPosition(), &_inputManager);
	////
	_spriteBacth.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, levels[currentLevel]->getWidth() - 2
	);
	std::uniform_int_distribution<int> randomY(
		1, levels[currentLevel]->getHeight() - 2
	);
	///
}

/*void MainGame::updateElements()
{
	player->update(levels[currentLevel]->getLevelData(),
		humano, zombies);

	for (size_t i = 0; i < humano.size(); i++)
	{
		humano[i]->update(levels[currentLevel]->getLevelData(),
			humano, zombies);
	}
}*/

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);

	/*GLuint timeLocation = 
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	levels[currentLevel]->draw();
	////
	player->draw(_spriteBacth);

	for (size_t i = 0; i < spritesGlobal.size(); i++)
	{
		spritesGlobal[i]->draw(_spriteBacth);
	}
	////
	_spriteBacth.end();
	_spriteBacth.renderBatch();
	/*glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("Textures/Paper_Mario_.png");
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBacth.draw(position, uv, texture.id,0.0f, color);
	_spriteBacth.draw(position + glm::vec4(50,0,0,0), uv, texture.id, 0.0f, color);
	_spriteBacth.end();
	_spriteBacth.renderBatch();*/

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x,
				event.motion.y);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		}
	}
	handleInput();
}

void MainGame::handleInput() {
	const float CAMERA_SPEED = 0.5f;
	const float SCALE_SPEED = 0.0005f;
	///////
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, levels[currentLevel]->getWidth() - 2
	);
	std::uniform_int_distribution<int> randomY(
		1, levels[currentLevel]->getHeight() - 2
	);//////////
	
	/*if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
		cout << mouseCoords.x << " " << mouseCoords.y << endl;
	}*/

	if (_inputManager.isKeyPressed(SDLK_a))
	{
		spritesGlobal.push_back(new SpriteGlobal());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		spritesGlobal.back()->init(pos, 'A');
	}
	if (_inputManager.isKeyPressed(SDLK_b))
	{
		spritesGlobal.push_back(new SpriteGlobal());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		spritesGlobal.back()->init(pos, 'B');
	}
	if (_inputManager.isKeyPressed(SDLK_c))
	{
		spritesGlobal.push_back(new SpriteGlobal());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		spritesGlobal.back()->init(pos, 'C');
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		spritesGlobal.push_back(new SpriteGlobal());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		spritesGlobal.back()->init(pos, 'D');
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		spritesGlobal.push_back(new SpriteGlobal());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		spritesGlobal.back()->init(pos, 'E');
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_r)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_camera.setPosition(player->getPosition());
		player->update();
	}
}


MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
