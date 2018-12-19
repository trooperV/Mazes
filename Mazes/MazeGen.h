#pragma once
#include "Maze.h"
#include "Node.h"
#include <queue>

class MazeGen
{
private:
	int cellSize_;
	int width_;
	int height_;
	bool loops_;
	Maze maze_;
	Node startNode_;
	Node endNode_;
	std::queue<Node> sol_;
	std::vector<Node> CreateNodeV();
public:
	MazeGen();
	~MazeGen();
	enum MazeType { RECURSIVE_BACKTRACKER = 0};
	enum SolveType { NONE = 0,  ASTAR = 1};
	void InitMaze(int width, int height, int cellSize, MazeType mazeType, SolveType solveType);
	Maze GetMaze();
	std::queue<Node> GetSol();
	int GetWidth();
	int GetHeight();
	int GetCellSize();
};

