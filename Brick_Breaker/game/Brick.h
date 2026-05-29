#pragma once
#include <raylib.h>
#include "Definitions.h"

class Brick
{
private:
	Color _color;
	Rectangle _rect;

	//int _maxHp = 1;
	//int _hp = 1;

	bool _active = true;
	bool _breakable = true;

public:
	Brick(const Color& color, const Rectangle& rect)
		: _color(color), _rect(rect)
	{

	}

	bool IsActive() const { return _active; }
	Rectangle GetRect() const { return _rect; }

	void Update()
	{

	}

	void Render() const
	{
		if (_active) 
		{ 
			//DrawRectangleRounded(_rect, 0.1f, 8, _color); 
			DrawRectangleRounded(_rect, 0.1f, 8, 
				Color{ (unsigned char)(_color.r * 0.7), (unsigned char)(_color.g * 0.7), (unsigned char)(_color.b * 0.7), _color.a });

			float xBuffer = (_rect.width - _rect.width * 0.9) / 2;
			float yBuffer = (_rect.height - _rect.height * 0.7) / 2;
			DrawRectangle(_rect.x + xBuffer, _rect.y + yBuffer, _rect.width * 0.9, _rect.height * 0.7, _color);

			

		}
	}
	void Deactivate() { _active = false; }
	void SetUnbreakable() { _breakable = false; }
	void Reset() { _active = true; }



};