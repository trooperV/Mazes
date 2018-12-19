#include "Game.h"

MazeGen mazeGen;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char * title, int xpos, int ypos, int width, int height, int cellSize, bool typeWxH, MazeGen::MazeType mazeType, MazeGen::SolveType solveType, bool fullscreen)
{
	if (typeWxH == 0) {
		if ((width / cellSize) % 2 == 0) {
			width = ((width + cellSize) / cellSize)*cellSize;
		}
		else {
			width = (width / cellSize)*cellSize;
		}

		if ((height / cellSize) % 2 == 0) {
			height = ((height + cellSize) / cellSize)*cellSize;
		}
		else {
			height = (height / cellSize)*cellSize;
		}
	}
	else if (typeWxH == 1) {
		if (width % 2 == 0) width++;
		if (height % 2 == 0) height++;
		width = width * cellSize;
		height = height * cellSize;
	}


	width_ = width;
	height_ = height;

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Subsystems Initialization Failed: " << SDL_GetError << std::endl;
	}
	else {
		std::cout << "Subsystems Initialised!" << std::endl;

		gWindow_ = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (gWindow_ == NULL) {
			std::cout << "Window Creation Failed: " << SDL_GetError << std::endl;
		}
		else {
			std::cout << "Window Created!" << std::endl;

			gRenderer_ = SDL_CreateRenderer(gWindow_, -1, 0);
			if (gRenderer_ == NULL) {
				std::cout << "Renderer Creation Failed: " << SDL_GetError << std::endl;
			}
			else {
				isRunning_ = true;
				SDL_SetRenderDrawColor(gRenderer_, 85, 107, 47, 255);
				std::cout << "Renderer Created!" << std::endl;
			}
		}
	}

	mazeGen.InitMaze(width_, height_, cellSize, mazeType, solveType);
}

int Game::GetWidth()
{
	return width_;
}

int Game::GetHeight()
{
	return height_;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning_ = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) isRunning_ = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	//no need for the maze
}

void Game::render()
{
	SDL_RenderClear(gRenderer_);
	//Draw Maze
	SDL_Rect curRect;
	curRect.w = mazeGen.GetCellSize();
	curRect.h = mazeGen.GetCellSize();

	for (int i = 0; i < mazeGen.GetWidth(); i++) { // /10
		for (int j = 0; j < mazeGen.GetHeight(); j++) {
			curRect.x = i * mazeGen.GetCellSize();
			curRect.y = j * mazeGen.GetCellSize();
			if (mazeGen.GetMaze().GetState(i, j) == Maze::PATH) {
				SDL_SetRenderDrawColor(gRenderer_, 255, 255, 255, 255);
				SDL_RenderFillRect(gRenderer_, &curRect);
			}
			else if (mazeGen.GetMaze().GetState(i, j) == Maze::WALL) {
				SDL_SetRenderDrawColor(gRenderer_, 0, 0, 0, 0);
				SDL_RenderFillRect(gRenderer_, &curRect);
			}
		}
	}

	while (!mazeGen.GetSol().empty())
	{
		curRect.x = mazeGen.GetSol().front().GetX() * mazeGen.GetCellSize();
		curRect.y = mazeGen.GetSol().front().GetY() * mazeGen.GetCellSize();
		SDL_SetRenderDrawColor(gRenderer_, 204, 0, 0, 0);
		SDL_RenderFillRect(gRenderer_, &curRect);
		mazeGen.GetSol().pop();
	}

	mazeGen.GetMaze().FreeMaze();
	//Draw Path

	SDL_RenderPresent(gRenderer_);
}

void Game::clear()
{
	SDL_DestroyWindow(gWindow_);
	SDL_DestroyRenderer(gRenderer_);
	SDL_Quit();
	std::cout << "Game Cleared!" << std::endl;
}

bool Game::running()
{
	return isRunning_;
}
