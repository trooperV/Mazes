#pragma once
//#include

class Maze
{
private:
	int width_;
	int height_;
	int *mazeMatrix_;

	int index (int xpos, int ypos) const;
public:
	Maze();
	Maze(int width, int height);
	~Maze();
	enum MazeState { UNVISITED = 0, PATH = 1, WALL = 2};
	void SetState(int xpos, int ypos, MazeState state);
	MazeState GetState(int xpos, int ypos);
	bool AllVisited();
	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
	void SetMatrix();
	void FreeMaze();
};

