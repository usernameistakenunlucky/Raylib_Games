#pragma once

enum class State
{
	GameOver = 0,
	LevelComplete,
	Paused,
	Play,
	Win,
};

enum class UiInput
{
	Nothing = 0,
	Unpause,
	Restart,
};

//screen
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 1280;

//lives
constexpr int MAX_LIVES = 3;

//bricks
constexpr int BRICKS_PER_ROW = 8;
constexpr int GAP = 12;
constexpr int BRICK_HEIGHT = 40;
constexpr Color RED_BRICK = Color(180, 54, 24, 255);

//player
constexpr int BOTTOM_GAP = 50;
constexpr int PLAYER_SPEED = 15;

//ball
constexpr int BALL_RADIUS = 20;
constexpr int BALL_SPEED = -15;
constexpr int TRAIL_LENGTH = 10;

//buttons
constexpr int BUTTON_WIDTH = 300;
constexpr int BUTTON_HEIGHT = 150;

inline void DrawHeart(Rectangle& rect, Color color)
{
	float size = rect.height;
	float radius = size / 2.0f;
	float centerX = rect.x + rect.width / 2.0f;
	float centerY = rect.y + rect.height / 2.0f;

	DrawCircle(centerX - radius / 2, centerY, radius / 2, color);
	DrawCircle(centerX + radius / 2, centerY, radius / 2, color);
	Vector2 v1 = { centerX - radius, centerY };
	Vector2 v2 = { centerX + radius, centerY };
	Vector2 v3 = { centerX,          centerY + radius * 1.5f };
	DrawTriangle(v2, v1, v3, color);
}