#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor gaaaa", width, height, 0);

	initShaders();

}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	sprite.init(-1,-1,1,1,("images/Teemo.png"));
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.02;
	sprite.draw();
	for (auto& sprite : sprites) {
		sprite.draw();
	}
	program.unuse();
	window->swapWindow();

}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		float currentTime = SDL_GetTicks() / 1000.0f;
		if (currentTime - lastSpawnTime > spawnInterval) {
			float randX = ((float)(rand() % 200) - 100) / 100.0f;
			float randY = ((float)(rand() % 200) - 100) / 100.0f;
			int randImage = (rand() % 3)+1;
			string image;
			if (randImage == 1) {
				image = "images/TaBien.png";
			}
			else if (randImage == 2) {
				image = "images/Mondongo.png";
			}
			else {
				image = "images/AmoGus.png";
			}
			sprites.emplace_back();
			sprites.back().init(randX, randY, 1, 1,image);
			lastSpawnTime = currentTime;
		}
		draw();
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
			cout << " Posicion en X " << event.motion.x 
			<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}
