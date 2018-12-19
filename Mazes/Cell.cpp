#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(int x, int y)
{
	x_ = x;
	y_ = y;
}

Cell::~Cell()
{
}

void Cell::SetX(int x)
{
	x_ = x;
}

void Cell::SetY(int y)
{
	y_ = y;
}

int Cell::GetX()
{
	return x_;
}

int Cell::GetY()
{
	return y_;
}
