#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include <ctime>
#include <vector>
#include "Window.h"
#include <vector>
#include"Camera2D.h"
#include "InputManager.h"
using namespace std;

enum class GameState {
	PLAY, EXIT
};

class MainGame {

private:
	vector<Sprite* > sprites;
	time_t timer;
	int selected_position;
	int width;
	int height;
	Window* window;
	Camera2D camera;
	void init();
	void processInput();
	void initShaders();
	void handelInput();
	GLS_Program program;
	float time = 0;
	InputManager inputManager;

	const float CAMERA_SPEED = 0.05f;
	const float CAMERA_SCALE = 0.1f;

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
