#pragma once
class Cell
{
protected:
	int x_;
	int y_;
public:
	Cell();
	Cell(int x, int y);
	~Cell();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
};

