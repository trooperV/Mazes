#include "Node.h"

Node::Node()
{
	gScore_ = std::numeric_limits<float>::max();
	fScore_ = std::numeric_limits<float>::max();
	//cameFrom_ = new Node();
	//Neighbors = new std::vector<Cell>();
}

Node::~Node()
{
}

void Node::SetCameFrom(Node *cameFrom)
{
	cameFrom_ = cameFrom;
}

Node Node::GetCameFrom()
{
	return *cameFrom_;
}

void Node::SetNeighbors(std::vector<Cell> neighbors)
{
	neighbors_ = neighbors;
}

std::vector<Cell> Node::GetNeighbors()
{
	return neighbors_;
}

void Node::SetGScore(float gScore)
{
	gScore_ = gScore;
}

float Node::GetGScore()
{
	return gScore_;
}

void Node::SetFScore(float fScore)
{
	fScore_ = fScore;
}

float Node::GetFScore()
{
	return fScore_;
}
