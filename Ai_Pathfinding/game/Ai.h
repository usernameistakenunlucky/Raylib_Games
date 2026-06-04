#pragma once
#include "raylib.h"
#include "Node.h"
#include "Definitions.h"
#include <vector>
#include <queue>
#include <stack>

class Ai
{
public:

	AiState _state = AiState::waiting;

	std::vector<std::vector<Node>> grid;
	Node* startPoint = nullptr;
	Node* endPoint = nullptr;

	Ai() {}

	void Main();
	void Start();
	void Restart();
	void UpdateAll();
	void RenderAll();
	void Interaction();

	Node* GetRandomNode();
	std::vector<Node*> GetNeighbors(Node* node);

	// BFS /////////////////////////////////////
	void BFS(Node* start, Node* end);
	std::vector<Node*> bfsTracedPath;
	std::queue<Node*> bfsOpenSet;
	bool bfsFoundEnd = false;
	Node* bfsEndTrace = nullptr;
	int drawBFSindex = 0;
	////////////////////////////////////////////
	// DFS /////////////////////////////////////
	void DFS(Node* start, Node* end);
	std::vector<Node*> dfsTracedPath;
	std::stack<Node*> dfsOpenSet;
	bool dfsFoundEnd = false;
	Node* dfsEndTrace = nullptr;
	int drawDFSindex = 0;
	////////////////////////////////////////////

	//void Djikstra(Node* start, Node* end);
	//void AStar(Node* start, Node* end);

	void RandomSearch(Node* start, Node* end);
	std::vector<Node*> currentPath;
	std::vector<Node*> currentVisited;
	bool searchComplete = false;

};