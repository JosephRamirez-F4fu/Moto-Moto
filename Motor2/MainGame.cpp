#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
	this->nextVboID = 1;
	std::time(&timer);
	selected_position = 0;


}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("OwO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		std::cerr << "Error al crear el contexto OpenGL: " << SDL_GetError() << std::endl;
		return;
	}
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(error) << std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	time += 0.2;
	drawSprite();
	program.unuse();
	SDL_GL_SwapWindow(window);

}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		draw();
		
		clearSprites();
		addSprite();
		processInput();
		
	}
}

void MainGame::addSprite()
{
	vector<float> position_down_right = { -1, 0, 1, 1 };
	vector<float> position_down_left = { -1, -1, 1, 1 };
	vector<float> position_up_right = { 0, 0, 1, 1 };
	vector<float> position_up_left = { 0, -1, 1, 1 };

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
		Sprite sprite(x, y, w, h, this->nextVboID);
		sprite.init();
		sprites.push_back(sprite);
		time_t timer_new;
		std::time(&timer_new);
		timer = timer_new;
		selected_position++;
		this->nextVboID++;
	}
}
void MainGame::drawSprite()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
}

void MainGame::clearSprites()
{
	std::cout << sprites.size() << std::endl;
	if (sprites.size() > 4) {
		sprites.clear();
		selected_position = 0;
		nextVboID = 1;
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
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShader();

}


