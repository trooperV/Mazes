#include "AStar.h"



std::queue<Node> AStar::ReconstructPath(Node start, Node current)
{
	std::queue<Node> totalPath;
	totalPath.push(current);

	while (!(current.GetX() == start.GetX() && current.GetY() == start.GetY())) // only x and y comparison
	{
		current = current.GetCameFrom();
		totalPath.push(current);
	}

	return totalPath;
}

float AStar::DistanceB2Nodes(Node node0, Node node1)
{
	return (float)sqrt(pow(node1.GetX() - node0.GetX(), 2) + pow(node1.GetY() - node0.GetY(), 2));
}

int AStar::MinFScore(std::vector<Node> set)
{
	int curMin = 0;
	float curMinV = std::numeric_limits<float>::max();
	for (int i = 0; i < set.size(); i++)
	{
		if (set[i].GetFScore() < curMinV)
		{
			curMin = i;
			curMinV = set[i].GetFScore();
		}
	}
	return curMin;
}

int AStar::FindIndexXY(Cell n)
{
	for (int i = 0; i < nodeV_.size(); i++)
	{
		if (nodeV_[i].GetX() == n.GetX() && nodeV_[i].GetY() == n.GetY())
		{
			return i;
		}
	}
	std::cout << "FindIndexXY Returns -1" << std::endl;
	return -1;
}

bool AStar::NodeSetContainsEl(std::vector<Node> nodeSet, Node temp)
{
	for (int i = 0; i < nodeSet.size(); i++)
	{
		if (nodeSet[i].GetX() == temp.GetX() && nodeSet[i].GetY() == temp.GetY()) return true;
	}

	return false;
}

AStar::AStar()
{

}

AStar::AStar(std::vector<Node> nodeV, Node startNode, Node endNode)
{
	nodeV_ = nodeV;
	startNode_ = startNode;
	startNode_.SetCameFrom(&startNode);
	endNode_ = endNode;
}


AStar::~AStar()
{
}

std::queue<Node> AStar::SolveMaze()
{
	//std::cout << current.GetX() << " " << current.GetY() << std::endl;
	/*std::cout << startNode_.GetX() << " " << startNode_.GetY() << std::endl;
	std::cout << endNode_.GetX() << " " << endNode_.GetY() << std::endl;*/

	std::vector<Node> closedSet;
	std::vector<Node> openSet;
	//std::cout << closedSet.size();
	startNode_.SetGScore(0);
	startNode_.SetFScore(DistanceB2Nodes(startNode_, endNode_));
	//std::cout << startNode_.GetCameFrom()->GetX();
	startNode_.SetCameFrom(&startNode_);
	/*startNode_.GetCameFrom().SetX(startNode_.GetX());
	startNode_.GetCameFrom().SetY(startNode_.GetY());
	startNode_.GetCameFrom().SetGScore(startNode_.GetGScore());
	startNode_.GetCameFrom().SetFScore(startNode_.GetFScore());
	startNode_.GetCameFrom().SetNeighbors(startNode_.GetNeighbors());*/
	//std::cout << startNode_.GetCameFrom().GetX() << std::endl;
	openSet.push_back(startNode_);
	Node current;
	while (!openSet.empty())
	{
		
		current.SetCameFrom(&openSet[MinFScore(openSet)].GetCameFrom());
		current = openSet[MinFScore(openSet)];
		//std::cout << current.GetCameFrom().GetX() << std::endl;
		//current.SetCameFrom(openSet[MinFScore(openSet)].GetCameFrom());
		if (current.GetX() == endNode_.GetX() && current.GetY() == endNode_.GetY())
		{	
			return ReconstructPath(startNode_, current); // current.camefrom is bad
		}

		openSet.erase(openSet.begin()+MinFScore(openSet));
		closedSet.push_back(current);

		for each (Cell n in current.GetNeighbors())
		{
			Node temp = nodeV_.at(FindIndexXY(n));
			if (NodeSetContainsEl(closedSet, temp)) continue;
			if (!NodeSetContainsEl(openSet, temp)) openSet.push_back(temp);

			float tentativeGScore = current.GetGScore() + DistanceB2Nodes(current, temp);
			if (tentativeGScore >= temp.GetGScore()) continue;
			//std::cout << current.GetCameFrom()->GetX() << std::endl;
			temp.SetCameFrom(&current);
			temp.SetGScore(tentativeGScore);
			temp.SetFScore(temp.GetGScore() + DistanceB2Nodes(temp, endNode_));
		}
	}

	return ReconstructPath(startNode_, current);
}