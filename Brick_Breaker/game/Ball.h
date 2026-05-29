#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Definitions.h"
#include "Brick.h"
#include "Player.h"

class Ball
{
private:
	std::vector<Vector2> _trail;

	Vector2 _position;
	Vector2 _speed = { 0,0 };
	int _radius = BALL_RADIUS;
	bool _active = false;

public:
	Ball();

	Ball(const Vector2& position);

	void Update(std::vector<Brick>& bricks, Player& player, int& score, int& _currentLevel);

	void CheckCollisionBricks(std::vector<Brick>& bricks, int& score);
	void CheckCollisionPlayer(Player& player);
	void CheckCollisionBorder(Player& player);

	void Render() const;
	void Reset();
};