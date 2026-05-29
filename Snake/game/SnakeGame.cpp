#include "SnakeGame.h"
#include <raylib.h>
#include <raymath.h>
#include "Definitions.h"

void SnakeGame::Main()
{
	Start();

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		UpdateAll();
		RenderAll();

		EndDrawing();
	}

	CloseWindow();
}

void SnakeGame::Start()
{
	Vector2 headPos = Vector2{ BORDER_GAP.x / 2, BORDER_GAP.y / 2 };
	_player.tail.emplace_back(Piece(headPos, DARKGREEN));
	_player.direction = Vector2{ TILE_SIZE, 0 }; // move as much a tile to the right initially
}

void SnakeGame::Interaction()
{
	if (IsKeyPressed(KEY_P))
	{
		switch (_state)
		{
		case play: _state = State::paused; break;
		case paused: _state = State::play; break;
		}
	}
	if (IsKeyPressed(KEY_R) && _state == State::gameOver) { Restart(); }

	if (!_player.canMove || _state == State::paused || _state == State::gameOver) { return; }

	// player controls
	if (_player.direction.y == 0)
	{
		/*DOWN      */if (IsKeyPressed(KEY_S)) { _player.direction = Vector2{ 0, TILE_SIZE }; _player.canMove = false; }
		/*UP   */else if (IsKeyPressed(KEY_W)) { _player.direction = Vector2{ 0, -TILE_SIZE }; _player.canMove = false; }
	}
	else if (_player.direction.x == 0)
	{
		/*RIGHT     */if (IsKeyPressed(KEY_D)) { _player.direction = Vector2{ TILE_SIZE, 0 }; _player.canMove = false; }
		/*LEFT */else if (IsKeyPressed(KEY_A)) { _player.direction = Vector2{ -TILE_SIZE, 0 }; _player.canMove = false; }
	}
}

void SnakeGame::UpdateAll()
{
	Interaction();
	if (!_state == State::play) { return; }

	_frameCount++;
	_player.Update(_frameCount);

	// check if player died
	if (_player.HitBorder() || _player.HitSelf()) { _state = State::gameOver; }

	// check if screen is full (win)
	if (_player.tail.size() == SCREEN_WIDTH / TILE_SIZE * SCREEN_HEIGHT / TILE_SIZE) { _state = State::complete; return; }

	//_pickup
	if (!_pickup.active)
	{
		_pickup.active = true;
		_pickup.NewRandomLocation(BORDER_GAP, _player);
	}

	if (_player.tail[0].position == _pickup.position)
	{
		_pickup.active = false;
		_player.AddPiece();
	}
}

void SnakeGame::Restart()
{
	_state = State::play;
	_player.tail.clear();
	Start();
}

void SnakeGame::RenderBreakScreen(const char* text, Color color)
{
	int fontSize = SCREEN_WIDTH / 8;
	int textMeasure = MeasureText(text, fontSize);
	DrawText(text, SCREEN_WIDTH / 2 - textMeasure / 2, SCREEN_HEIGHT / 2 - fontSize / 2, fontSize, color);
}

void SnakeGame::RenderBoard()
{
	// black borders
	DrawRectangle(0, 0, SCREEN_WIDTH, BORDER_GAP.y / 2, BLACK); // top
	DrawRectangle(0, SCREEN_HEIGHT - BORDER_GAP.y / 2, SCREEN_WIDTH, BORDER_GAP.y / 2, BLACK); // bottom
	DrawRectangle(0, 0, BORDER_GAP.x / 2, SCREEN_HEIGHT, BLACK); // left
	DrawRectangle(SCREEN_WIDTH - BORDER_GAP.x / 2, 0, BORDER_GAP.x / 2, SCREEN_HEIGHT, BLACK); // right

	// vertial lines
	for (int i = 0; i < SCREEN_WIDTH / TILE_SIZE + 1; i++)
	{
		int yTop = BORDER_GAP.y / 2;
		int yBottom = SCREEN_HEIGHT - BORDER_GAP.y / 2;

		int x = BORDER_GAP.x / 2 + i * TILE_SIZE;

		Vector2 start = Vector2{ (float)x, (float)yTop };
		Vector2 end = Vector2{ (float)x, (float)yBottom };
		DrawLineEx(start, end, 4.f, WHITE);
	}
	// horozontal lines
	for (int i = 0; i < SCREEN_HEIGHT / TILE_SIZE + 1; i++)
	{
		int xLeft = BORDER_GAP.x / 2;
		int xRight = SCREEN_WIDTH - BORDER_GAP.x / 2;

		int y = BORDER_GAP.y / 2 + i * TILE_SIZE;

		Vector2 start = Vector2{ (float)xLeft, (float)y };
		Vector2 end = Vector2{ (float)xRight, (float)y };
		DrawLineEx(start, end, 4.f, WHITE);
	}

}

void SnakeGame::RenderAll()
{
	if (_state == State::gameOver) { RenderBreakScreen("Game Over", RED); return; }
	if (_state == State::complete) { RenderBreakScreen("You Win!", GREEN); return; }
	if (_state == State::paused) { RenderBreakScreen("Game Paused", YELLOW); return; }

	RenderBoard();
	_pickup.Render();
	_player.Render();

}


