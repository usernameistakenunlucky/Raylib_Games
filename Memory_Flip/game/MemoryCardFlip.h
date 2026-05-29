#pragma once
#include <raylib.h>
#include <vector>
#include "Card.h"

class MemoryCardFlip
{
private:

	std::vector<int> _numbers;
	std::vector<Card> _cards;

	Card* _firstPick = nullptr;
	Card* _secondPick = nullptr;

	float _flipBackTimer = 0.0f;
	float _hintTimer = HINT_TIMER;

	int _hints = 3;
	int _attemps = 0;
	int _gridSize = GRID_SIZE; // 6, 8, 10, 12

	GameState _gameState = GameState::play;

public:
	MemoryCardFlip();

	void Start();
	void Main();
	void UpdateAll();
	void RenderAll();

	void CheckIfGameOver();

};