#pragma once
#include <raylib.h>
#include "Definitions.h"

class Player
{
private:
	Vector2 _position;
	Vector2 _size;
	int _currentLives;

	int _bounceEffectCd = 0;

public:
	Player(const Vector2& position, const Vector2& size)
		: _position(position), _size(size), _currentLives(MAX_LIVES)
	{

	}

	Rectangle GetRect() const { return Rectangle(_position.x, _position.y, _size.x, _size.y); }
	Vector2 GetCenter() const { return Vector2(_position.x + _size.x / 2, _position.y + _size.y / 2); }
	Vector2 GetPos() const { return _position; }
	Vector2 GetSize() const { return _size; }
	int GetLives() const { return _currentLives; }

	void LoseLife() { _currentLives--; }
	void Bounce() { _bounceEffectCd = 10; }

	void Update()
	{
		if (IsKeyDown(KEY_A))
		{
			_position.x -= PLAYER_SPEED;
			if (_position.x < 0) { _position.x = 0; }
		}
		if (IsKeyDown(KEY_D))
		{
			_position.x += PLAYER_SPEED;
			if (_position.x > SCREEN_WIDTH - _size.x) { _position.x = SCREEN_WIDTH - _size.x; }
		}

		if (_bounceEffectCd > 0)
		{
			_bounceEffectCd -= 2;
		}
	}

	void Render() const
	{
		Vector2 currentPosition = Vector2{_position.x, _position.y + _bounceEffectCd};

		DrawRectangleRounded(Rectangle{ currentPosition.x, currentPosition.y, _size.x, _size.y }, 1.f, 16, { 173, 216, 255, 255 });
		Rectangle innerRect = { currentPosition.x + 5, currentPosition.y + 10, _size.x - 10, _size.y - 10 };
		DrawRectangleRounded(innerRect, 1.f, 16, { 20, 20, 180, 255 });
	}

	void ResetPos()
	{
		_position = Vector2{ /*X*/ (GetScreenWidth() / 2) - (_size.x / 2), /*Y*/ GetScreenHeight() - _size.y - BOTTOM_GAP};
	}

	void ResetLives()
	{
		_currentLives = MAX_LIVES;
	}

};