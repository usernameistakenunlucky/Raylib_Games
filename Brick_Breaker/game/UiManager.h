#pragma once
#include <raylib.h>
#include <string>
#include "Player.h"

class UiManager
{
private:

public:
	Rectangle _pauseButton = { (SCREEN_WIDTH / 2) - (BUTTON_WIDTH / 2), (SCREEN_HEIGHT / 2) - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };
	Rectangle _restartButton = { (SCREEN_WIDTH / 2) - (BUTTON_WIDTH / 2), (SCREEN_HEIGHT / 2) - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT };

	UiManager()
	{
	}

	UiInput Update(State& state)
	{
		if (state == State::GameOver)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), _restartButton))
			{
				state = State::Play;
				return UiInput::Restart;
			}
		}
		else if (state == State::Win)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), _restartButton))
			{
				state = State::Play;
				return UiInput::Restart;
			}
		}
		else if (state == State::Paused)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), _pauseButton))
			{
				state = State::Play;
				return UiInput::Unpause;
			}
		}
		else { return UiInput::Nothing; }
	}

	void Render(const Player& player, const int& score, const int& level, State& state)
	{
		RenderLives(player);
		int uiFont = 40;
		std::string scoreText = "Score : " + std::to_string(score);
		DrawText(scoreText.c_str(), 850, SCREEN_HEIGHT - uiFont - 5, uiFont, GOLD);

		std::string levelText = "Lvl : " + std::to_string(level);
		DrawText(levelText.c_str(), 1140, SCREEN_HEIGHT - uiFont - 5, uiFont, GOLD);

		if (state == State::GameOver)
		{
			DrawRectangleRec(_restartButton, LIGHTGRAY);
			DrawText("GAME OVER", 25, 20, 200, WHITE);
			DrawText("RESTART", _pauseButton.x + 5, _pauseButton.y + 5, 50, BLACK);
		}
		if (state == State::Paused)
		{
			DrawRectangleRec(_pauseButton, LIGHTGRAY);
			DrawText("PAUSED", 100, 20, 250, WHITE);
			DrawText("RESUME", _pauseButton.x + 5, _pauseButton.y + 5, 50, BLACK);
		}
		if (state == State::Win)
		{
			DrawRectangleRec(_restartButton, LIGHTGRAY);
			DrawText(" YOU WIN ", 25, 20, 200, WHITE);
			DrawText("RESTART", _pauseButton.x + 5, _pauseButton.y + 5, 50, BLACK);
		}
	}

	void RenderLives(const Player& player)
	{
		int livesToDraw = player.GetLives();
		int livesSize = 30;
		int loop = 0;
		while (loop < MAX_LIVES)
		{
			int spacer = 10;
			Rectangle lifeRect = { loop * (livesSize * 1.5) + spacer, SCREEN_HEIGHT - livesSize - spacer, livesSize , livesSize };
			if (livesToDraw > 0)
			{
				DrawHeart(lifeRect, RED);
				livesToDraw--;
			}
			else
			{
				DrawHeart(lifeRect, BLACK);
			}
			loop++;
		}
	}
};