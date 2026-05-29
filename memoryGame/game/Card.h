#pragma once
#include <raylib.h>
#include <string>
#include "Definitions.h"

class Card
{
private:

	int _value;
	std::string _text;
	Rectangle _cardRect;
	Vector2 _valuePosition;
	Vector2 _qmPosition;
	Color _color;

	CardState _state = CardState::hidden;

public:
	Card(const int& value, const Rectangle& cardRect, const Color& color)
		: _value(value), _cardRect(cardRect), _color(color)
	{
		_text = std::to_string(_value);
		int textWidth = MeasureText(_text.c_str(), UI_FONT);
		int textX = _cardRect.x + (_cardRect.width - textWidth) / 2;
		int textY = _cardRect.y + (_cardRect.height - UI_FONT) / 2;

		_valuePosition = { (float)textX, (float)textY };


		int qmX = _cardRect.x + (_cardRect.width - QM_WIDTH) / 2;
		int qmY = _cardRect.y + (_cardRect.height - UI_FONT) / 2;

		_qmPosition = { (float)qmX, (float)qmY };
	}

	int GetValue()const { return _value; }
	CardState GetState() const { return _state; }

	void SetState(const CardState& state) { _state = state; }

	bool Update()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionPointRec(GetMousePosition(), _cardRect) &&
			_state == CardState::hidden)
		{
			_state = CardState::flipped;
			return true;
		}
		return false;
	}

	void Render()
	{
		switch (_state)
		{
		/**/case CardState::hidden:
		{
			DrawRectangleRounded(_cardRect, 0.2f, 5, BLACK);
			std::string hiddenText = "?";
			DrawText(hiddenText.c_str(), _qmPosition.x, _qmPosition.y, UI_FONT, WHITE);
			break;

		}
		/**/case CardState::matched:
		{
			std::string matchedText = ":)";
			DrawRectangleRounded(_cardRect, 0.2f, 5, GOLD);
			DrawText(matchedText.c_str(), _qmPosition.x, _qmPosition.y, UI_FONT, WHITE);
			break;

		}
		/**/case CardState::flipped:
		{
			DrawRectangleRounded(_cardRect, 0.2f, 5, _color);
			DrawText(_text.c_str(), _valuePosition.x, _valuePosition.y, UI_FONT, WHITE);
			break;

		}
		}
	}

	void DisplayHint()
	{
		DrawRectangleRounded(_cardRect, 0.2f, 5, _color);
		DrawText(_text.c_str(), _valuePosition.x, _valuePosition.y, UI_FONT, WHITE);
	}


};