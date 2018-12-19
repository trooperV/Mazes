#pragma once
#include "Cell.h"
#include <vector>
#include <limits>

class Node : public Cell
{
private:
	float gScore_;
	float fScore_;
	Node *cameFrom_;
	std::vector<Cell> neighbors_;
public:
	Node();
	~Node();
	void SetCameFrom(Node *cameFrom);
	Node GetCameFrom();
	void SetNeighbors(std::vector<Cell> neighbors);
	std::vector<Cell> GetNeighbors();
	void SetGScore(float gScore);
	float GetGScore();
	void SetFScore(float fScore);
	float GetFScore();
};

