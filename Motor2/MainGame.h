#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include <ctime>
#include <vector>
using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame {

private:
	vector<Sprite> sprites;
	time_t timer;
	int selected_position;
	GLuint nextVboID;
	int width;
	int height;
	SDL_Window* window;
	void init();
	void processInput();
	void initShaders();
	GLS_Program program;
	float time = 0;
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
	void addSprite();
	void drawSprite();
	void clearSprites();


};
