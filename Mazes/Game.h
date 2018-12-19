#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "MazeGen.h"
#include "Maze.h"

class Game
{
private:
	int width_;
	int height_;
	bool isRunning_ = false;
	SDL_Window* gWindow_;
	SDL_Renderer* gRenderer_;

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, int cellSize, bool typeWxH, MazeGen::MazeType mazeType, MazeGen::SolveType solveType, bool fullscreen);

	int GetWidth();

	int GetHeight();

	void handleEvents();
	void update();
	void render();
	void clear();

	bool running();
};

