#include "Game.h"

Game* game;

int width = 1080;
int height = 720;
int cellSize = 5;
bool typeWxH = false;
MazeGen::MazeType mazeType = MazeGen::RECURSIVE_BACKTRACKER;
MazeGen::SolveType solveType = MazeGen::NONE;

int wmain(int argc, char *argv[]) {
	game = new Game();

	game->init("Mazes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, cellSize, typeWxH, mazeType, solveType, false);

	game->render();
	while (game->running()) {
		game->handleEvents();
		//game->update();
	}

	game->clear();
	delete game;

	return 0;
}