#include "MazeGen.h"
#include "Maze.h"
#include "RecursiveBacktracker.h"
#include "AStar.h"
#include <iostream>


std::vector<Node> MazeGen::CreateNodeV()
{
	std::vector<Node> nodeV;
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < height_; j++)
		{
			if (maze_.GetState(i, j) == Maze::PATH)
			{
				Node cur;
				cur.SetX(i);
				cur.SetY(j);

				std::vector<Cell> neighbors;

				if (i + 1 < width_ && maze_.GetState(i + 1, j) == Maze::PATH) neighbors.push_back(Cell(i + 1, j));
				if (i - 1 >= 0 && maze_.GetState(i - 1, j) == Maze::PATH) neighbors.push_back(Cell(i - 1, j));
				if (j + 1 < height_ && maze_.GetState(i, j + 1) == Maze::PATH) neighbors.push_back(Cell(i, j + 1));
				if (j - 1 >= 0 && maze_.GetState(i, j - 1) == Maze::PATH) neighbors.push_back(Cell(i, j - 1));

				cur.SetNeighbors(neighbors);
				if (i == 1 && j == 1)
				{
					startNode_ = cur;
				}

				if (i == width_-2 && j == height_ - 2)
				{
					endNode_ = cur;
				}
				nodeV.push_back(cur);
			}
		}
	}

	return nodeV;
}

MazeGen::MazeGen()
{
}


MazeGen::~MazeGen()
{
}

void MazeGen::InitMaze(int width, int height, int cellSize, MazeType mazeType, SolveType solveType)
{
	cellSize_ = cellSize;
	width_ = width / cellSize_;
	height_ = height / cellSize_;

	switch (mazeType)
	{
	case MazeGen::RECURSIVE_BACKTRACKER:
	{
		RecursiveBacktracker reB(width_, height_);
		maze_ = reB.CreateMaze();
	}
	break;
	default:
		break;
	}

	switch (solveType)
	{
	case MazeGen::NONE:
		break;
	case MazeGen::ASTAR:{
		std::vector<Node> nodeV = CreateNodeV();
		AStar aStar(nodeV, startNode_, endNode_);
		sol_ = aStar.SolveMaze();
	}
	break;
	default:
		break;
	}
}

Maze MazeGen::GetMaze()
{
	return maze_;
}

std::queue<Node> MazeGen::GetSol()
{
	return sol_;
}

int MazeGen::GetWidth()
{
	return width_;
}

int MazeGen::GetHeight()
{
	return height_;
}

int MazeGen::GetCellSize()
{
	return cellSize_;
}
