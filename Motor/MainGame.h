#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "Sprite.h"
#include "GLS_Program.h"
using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame {

private:
	vector<Sprite> sprites;
	Sprite sprite;
	Sprite sprite2;
	int width;
	int height;
	SDL_Window* window;
	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;

	float spawnInterval = 2.0f; 
	float lastSpawnTime = 0.0f; 
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();


};
