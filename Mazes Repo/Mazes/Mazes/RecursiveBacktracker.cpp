#include "RecursiveBacktracker.h"
#include <ctime>
#include <cstdlib>

int RecursiveBacktracker::NumUnvisitedNeighbors(Cell curCell)
{
	int count = 0;

	if (curCell.GetY() + 2 < maze_->GetHeight() && maze_->GetState(curCell.GetX(), curCell.GetY() + 2) == Maze::UNVISITED) count++;
	if (curCell.GetX() - 2 > 0 && maze_->GetState(curCell.GetX() - 2, curCell.GetY()) == Maze::UNVISITED) count++;
	if (curCell.GetX() + 2 < maze_->GetWidth() && maze_->GetState(curCell.GetX() + 2, curCell.GetY()) == Maze::UNVISITED) count++;
	if (curCell.GetY() - 2 > 0 && maze_->GetState(curCell.GetX(), curCell.GetY() - 2) == Maze::UNVISITED) count++;

	if (count == 0) return -1;

	return count;
}

Cell RecursiveBacktracker::RandomCellNeighbor(Cell curCell, int dir)
{
	if (curCell.GetY() + 2 < maze_->GetHeight() && maze_->GetState(curCell.GetX(), curCell.GetY() + 2) == Maze::UNVISITED)
	{
		dir--;
		if (dir == 0)
		{
			maze_->SetState(curCell.GetX(), curCell.GetY() + 1, Maze::PATH);
			return Cell(curCell.GetX(), curCell.GetY() + 2);
		}
	}

	if (curCell.GetX() - 2 > 0 && maze_->GetState(curCell.GetX() - 2, curCell.GetY()) == Maze::UNVISITED)
	{
		dir--;
		if (dir == 0)
		{
			maze_->SetState(curCell.GetX() - 1, curCell.GetY(), Maze::PATH);
			return Cell(curCell.GetX() - 2, curCell.GetY());
		}
	}

	if (curCell.GetX() + 2 < maze_->GetWidth() && maze_->GetState(curCell.GetX() + 2, curCell.GetY()) == Maze::UNVISITED)
	{
		dir--;
		if (dir == 0)
		{
			maze_->SetState(curCell.GetX() + 1, curCell.GetY(), Maze::PATH);
			return Cell(curCell.GetX() + 2, curCell.GetY());
		}
	}
	if (curCell.GetY() - 2 > 0 && maze_->GetState(curCell.GetX(), curCell.GetY() - 2) == Maze::UNVISITED)
	{
		dir--;
		if (dir == 0)
		{
			maze_->SetState(curCell.GetX(), curCell.GetY() - 1, Maze::PATH);
			return Cell(curCell.GetX(), curCell.GetY() - 2);
		}
	}
	return curCell;
}

int RecursiveBacktracker::Random(int a, int b)
{
	return a + rand() % (b - a);
}

RecursiveBacktracker::RecursiveBacktracker()
{
}

RecursiveBacktracker::RecursiveBacktracker(int width, int height)
{
	if (width % 2 == 0) width--;
	if (height % 2 == 0) height--;

	width_ = width;
	height_ = height;

	maze_ = new Maze(width, height);
	curCell_.SetX(1);
	curCell_.SetY(1);

	srand(std::time(nullptr));
}


RecursiveBacktracker::~RecursiveBacktracker()
{
	//delete maze;
}

Maze RecursiveBacktracker::CreateMaze()
{
	Cell startingC = curCell_;
	maze_->SetState(curCell_.GetX(), curCell_.GetY(), Maze::PATH);
	while (!maze_->AllVisited()) {
		int nCells = RecursiveBacktracker::NumUnvisitedNeighbors(curCell_);
		if (nCells != -1) {
			int dir = RecursiveBacktracker::Random(1, nCells + 1);
			Cell nCell = RecursiveBacktracker::RandomCellNeighbor(curCell_, dir);
			storedCells_.push(curCell_);
			curCell_ = nCell;
			maze_->SetState(curCell_.GetX(), curCell_.GetY(), Maze::PATH);
		}
		else {
			if (!storedCells_.empty()) {
				curCell_ = storedCells_.top();
				storedCells_.pop();
			}
		}
	}
	return *maze_;
}
