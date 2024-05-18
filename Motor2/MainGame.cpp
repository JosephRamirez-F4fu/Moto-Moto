#include "MainGame.h"
#include "Sprite.h"



MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
	std::time(&timer);
	selected_position = 0;
	camera.init(width, height);
	inputManager = InputManager();


}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Game Engine", width, height, 0);
	initShaders();

}

MainGame::~MainGame()
{

}


void MainGame::run()
{
	init();
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 2);
	time += 0.2;
	glm::mat4 cameraMatrix = camera.getCameraMatrix();
	GLuint pLocation = program.getUniformLocation("Pos");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	drawSprite();
	program.unuse();
	window->swapWindow();

}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		
		clearSprites();
		addSprite();

		processInput(); 
		draw();
		camera.update();
		
	}
}

void MainGame::addSprite()
{
	vector<float> position_down_right = { -1, 0, 1, 1 };
	vector<float> position_down_left = { -1, -1, 1, 1 };
	vector<float> position_up_right = { 0, 0, 1, 1 };
	vector<float> position_up_left = { 0, -1, 1, 1 };
	vector<string> list_images = { "images/kirby_up.png", "images/franky.png", "images/brook.png", "images/chopper.png" };

	vector<vector<float>> list_positions
		= { position_down_right, position_down_left, position_up_right, position_up_left };

	time_t end;
	std::time(&end);
	if (difftime(end, timer) > 0.5) {
		vector<float>& position = list_positions[selected_position % list_positions.size()];
		float x = position[0];
		float y = position[1];
		float w = position[2];
		float h = position[3];
	
		sprites.push_back( new Sprite(x, y, w, h, list_images[selected_position % list_images.size()]));
		sprites.back()->init();
		time_t timer_new;
		std::time(&timer_new);
		timer = timer_new;
		selected_position++;
	}
}
void MainGame::drawSprite()
{
	for (size_t i = 0; i < sprites.size(); i++) {
		sprites[i]->draw();
		//cout << "Dibujando sprite" << endl;
	}
}

void MainGame::clearSprites()
{
	std::cout << sprites.size() << std::endl;
	if (sprites.size() > 4) {
		sprites.clear();
		selected_position = 0;
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			/*cout << " Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;*/
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		}
	}
	handelInput();
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.vert", "Shaders/colorShaderFrag.frag");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.addAttribute("vertexUV");
	program.linkShader();

}

void MainGame::handelInput()
{
	if (inputManager.isKeyDown(SDLK_w)) {
		cout << "up" << endl;
		camera.setPosition(camera.getPosition() + glm::vec2(0.0f,-CAMERA_SPEED));

	}
	if (inputManager.isKeyDown(SDLK_s)) {
		cout << "down" << endl;
		camera.setPosition(camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (inputManager.isKeyDown(SDLK_a)) {
		cout << "left" << endl;
		camera.setPosition(camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (inputManager.isKeyDown(SDLK_d)) {
		cout << "right" << endl;
		camera.setPosition(camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (inputManager.isKeyDown(SDLK_q)) {
		cout << "zoom in" << endl;
	}
	if (inputManager.isKeyDown(SDLK_e)) {
		cout << "zoom out" << endl;
	}
}


