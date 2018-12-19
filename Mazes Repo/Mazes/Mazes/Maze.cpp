#include "Maze.h"

int Maze::index(int xpos, int ypos) const
{
	return ypos*width_ + xpos;
}

Maze::Maze()
{
	mazeMatrix_ = new int[width_*height_];
}

Maze::Maze(int width, int height)
{
	mazeMatrix_ = new int[width*height];
	width_ = width;
	height_ = height;


	for (int i = 0; i < width*height; i++)
	{
		mazeMatrix_[i] = Maze::WALL;
	}

	for (int i = 1; i < width - 1; i += 2)
	{
		for (int j = 1; j < height - 1; j += 2)
		{
			mazeMatrix_[index(i, j)] = Maze::UNVISITED;
		}
	}
}

Maze::~Maze()
{
}

void Maze::SetState(int xpos, int ypos, MazeState state)
{
	mazeMatrix_[index(xpos, ypos)] = state;
}

Maze::MazeState Maze::GetState(int xpos, int ypos)
{
	switch (mazeMatrix_[index(xpos, ypos)])
	{
	case 0:
		return Maze::UNVISITED;
	case 1:
		return Maze::PATH;
	case 2:
		return Maze::WALL;
	default:
		return Maze::UNVISITED;
	}
}

bool Maze::AllVisited()
{
	for (int i = 0; i < width_*height_; i++)
	{
		if (mazeMatrix_[i] == Maze::UNVISITED)
		{
			return false;
		}
	}
	return true;
}

int Maze::GetWidth()
{
	return width_;
}

int Maze::GetHeight()
{
	return height_;
}

void Maze::SetWidth(int width)
{
	width_ = width;
}

void Maze::SetHeight(int height)
{
	height_ = height;
}

void Maze::SetMatrix()
{
	mazeMatrix_ = new int[width_*height_];
}

void Maze::FreeMaze(){
	delete[] mazeMatrix_;
}
