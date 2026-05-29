#pragma once
#include <raylib.h>
#include <vector>
#include "Definitions.h"
#include "Piece.h"
#include "Pickup.h"
#include "Player.h"

enum State
{
	play,
	paused,
	gameOver,
	complete,
};

class SnakeGame
{
private:

	Pickup _pickup;
	Player _player;

	State _state = State::play;
	int _frameCount = 0;
	

public:
	SnakeGame() {}
	void Main();
	void Start();
	void Interaction();
	void UpdateAll();
	void RenderAll();

	void Restart();
	void RenderBoard();
	void RenderBreakScreen(const char* text, Color color);
};