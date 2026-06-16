#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "Definitions.h"
#include "Piece.h"
#include "Pickup.h"
#include "FoodPickup.h"
#include "MagicPickup.h"
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

	std::unique_ptr<Pickup> _foodPickup;
	std::unique_ptr<Pickup> _magicPickup;
	std::vector<std::vector<Tile>> grid;
	Player _player;

	State _state = State::play;
	int _frameCount = 0;

	int _level = 1;

public:
	SnakeGame() {}
	void Main();
	void Start();
	void Interaction();
	void UpdateAll();
	void RenderAll();

	Vector2 RandomLocation();
	void SpawnFoodPickup();
	void SpawnMagicPickup();

	void Restart();
	void RenderBoard();
	void RenderBreakScreen(const char* text, Color color);
};