#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "Node.h"

class AStar
{
private:
	Node startNode_;
	Node endNode_;
	std::vector<Node> nodeV_;
	std::queue<Node> ReconstructPath(Node start, Node current);
	float DistanceB2Nodes(Node node0, Node node1);
	int MinFScore(std::vector<Node> set);
	int FindIndexXY(Cell n);
	bool NodeSetContainsEl(std::vector<Node> nodeSet, Node temp);
public:
	AStar();
	AStar(std::vector<Node> nodeV, Node startNode, Node endNode);
	~AStar();
	std::queue<Node> SolveMaze();
};