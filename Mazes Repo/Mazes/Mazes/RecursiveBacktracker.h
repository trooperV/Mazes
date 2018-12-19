#pragma once
#include "Maze.h"
#include "Cell.h"
#include <stack>

class RecursiveBacktracker
{
private:
	int width_;
	int height_;
	Cell curCell_;
	std::stack<Cell> storedCells_;
	Maze *maze_;
	int NumUnvisitedNeighbors(Cell curCell);
	Cell RandomCellNeighbor(Cell curCell, int dir);
	int Random(int a, int b);
public:
	RecursiveBacktracker();
	RecursiveBacktracker(int width, int height);
	~RecursiveBacktracker();
	Maze CreateMaze();
};

