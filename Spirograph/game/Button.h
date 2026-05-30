#pragma once
#include <raylib.h>

class Button
{
private:
	Rectangle _box;
	Color _color;
	bool _isSelected;

	bool IsMouseOverBox() const
	{
		return CheckCollisionPointRec(GetMousePosition(), _box);
	}

public:
	Button(float x, float y, float width, float height, Color color)
		: _color(color)
	{
		_box = Rectangle{ x, y, width, height };
		_isSelected = false;
	}

	void SetSelected(bool set) { _isSelected = set; }

	Color GetColor() const { return _color; }

	bool IsMouseClickingBox()
	{
		return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverBox());
	}

	void Update(Color currentColor)
	{
		if (!ColorIsEqual(_color, currentColor)) { _isSelected = false; }
	}

	void Render() const
	{

		if (IsMouseOverBox()) 
		{
			DrawRectangle(_box.x, _box.y, _box.width, _box.height, ColorBrightness(_color, 0.5f));
		}
		else
		{
			DrawRectangle(_box.x, _box.y, _box.width, _box.height, _color);
		}

		if (_isSelected)
		{
			DrawRectangleLinesEx(_box, 5, WHITE);
		}

	}

};