#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Definitions.h"

#include "UiManager.h"
#include "Level.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

// for doing vector2 += vector2
/*
inline Vector2& operator+=(Vector2& left, const Vector2& right) 
{
	left.x += right.x;
	left.y += right.y;
	return left;
}
*/

class WallBreaker
{
private:
	std::vector<Level> _levels;

	UiManager _ui;
	Player* _player = nullptr;
	Ball _ball;
	int _currentLevel = 1;
	int _score = 0;

	State _state = State::Play;

public:
	WallBreaker();

	void Main(); // anything to do with raylib itself
	void Start(); // anything in the beginning - unity style
	void InitializePlayer();
	void InitializeLevels();
	void InitializeBall();

	Level& CurrentLevel() { return _levels[_currentLevel - 1]; }

	void CheckIfLevelComplete();

	void UpdateAll(); // ongoing on the frames - unity style
	void RenderAll();

	void Restart();
	void NextLevel();
};