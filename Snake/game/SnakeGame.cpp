#include "SnakeGame.h"

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "Tile.h"
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
	//initialize grid
	for (int row = 0; row < ROWS; row++)
	{
		std::vector<Tile> rowOfTiles;

		for (int col = 0; col < COLUMNS; col++)
		{
			Tile newTile(row, col, false);
			if (GetRandomValue(0, 15) == 0) newTile.blocked = true;
			rowOfTiles.push_back(newTile);
		}
		grid.emplace_back(rowOfTiles);
	}

	Vector2 headPos = Vector2{ BORDER_GAP.x / 2, BORDER_GAP.y / 2 };
	_player.tail.emplace_back(Piece(headPos, DARKGREEN));
	_player.direction = Vector2{ TILE_SIZE, 0 }; // move as much a tile to the right initially

	SpawnFoodPickup();
	SpawnMagicPickup();
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
	DELTA_TIME = GetFrameTime();
	Interaction();
	if (!_state == State::play) { return; }
	_frameCount++;

	// send the food pickup to player for aStar to target
	int pickupCol = (int)((_foodPickup->position.x - BORDER_GAP.x / 2) / TILE_SIZE);
	int pickupRow = (int)((_foodPickup->position.y - BORDER_GAP.y / 2) / TILE_SIZE);
	Tile* pickupTile = (&grid[pickupRow][pickupCol]);

	_player.Update(_frameCount, grid, pickupTile);
	_foodPickup->Update();
	_magicPickup->Update();

	// check if player died
	if (_player.HitBorder() || _player.HitSelf() || _player.HitWall(grid)) { _state = State::gameOver; }

	// check if screen is full (win)
	if (_player.tail.size() == SCREEN_WIDTH / TILE_SIZE * SCREEN_HEIGHT / TILE_SIZE) { _state = State::complete; return; }

	// food pickup
	if (_foodPickup->active == false) { SpawnFoodPickup(); }
	else if (_player.tail[0].position == _foodPickup->position)
	{
		_foodPickup->Effect(_player);
		_foodPickup->active = false;
	}

	// magic pickup
	if (_magicPickup->active && 
		_player.tail[0].position == _magicPickup->position)
	{
		_magicPickup->Effect(_player);
		_magicPickup->active = false;
	}
	if (_frameCount % (5 * GetFPS() + 1) == 0) // every 5 seconds, either spawn or despawn the magic fruit
	{
		if (_magicPickup->active) { _magicPickup->active = false; }
		else { SpawnMagicPickup(); }
	}
}

Vector2 SnakeGame::RandomLocation()
{
	int x;
	int y;
	bool loop = true;
	while (loop)
	{
		x = GetRandomValue(0, SCREEN_WIDTH / TILE_SIZE - 1) * TILE_SIZE + BORDER_GAP.x / 2;
		y = GetRandomValue(0, SCREEN_HEIGHT / TILE_SIZE - 1) * TILE_SIZE + BORDER_GAP.y / 2;

		for (int i = 0; i < _player.tail.size(); i++)
		{
			if (x == _player.tail[i].position.x && y == _player.tail[i].position.y ||
				grid[(y - BORDER_GAP.y / 2) / TILE_SIZE][(x - BORDER_GAP.x / 2) / TILE_SIZE].blocked) // check if tile is blocked too
			{
				break;
			}
			if (i == _player.tail.size() - 1)
			{
				loop = false;
			}
		}
	}
	return Vector2{ (float)x, (float)y };
}

void SnakeGame::SpawnFoodPickup()
{
	//if (GetRandomValue(0, 4) == 0) { _pickup = std::make_unique<MagicPickup>(RandomLocation()); }
	_foodPickup = std::make_unique<FoodPickup>(RandomLocation());
}

void SnakeGame::SpawnMagicPickup()
{
	_magicPickup = std::make_unique<MagicPickup>(RandomLocation());
}

void SnakeGame::Restart()
{
	_state = State::play;
	_player.Reset();
	grid.clear();
	Start();
}

void SnakeGame::RenderBreakScreen(const char* text, Color color)
{
	int fontSize = SCREEN_WIDTH / 8;
	int textMeasure = MeasureText(text, fontSize);
	DrawText(text, SCREEN_WIDTH / 2 - textMeasure / 2, SCREEN_HEIGHT / 2 - fontSize / 2, fontSize, color);

	fontSize = SCREEN_WIDTH / 16;
	std::string score = "Score : " + std::to_string(_player.score);
	textMeasure = MeasureText(score.c_str(), fontSize);
	DrawText(score.c_str(), SCREEN_WIDTH / 2 - textMeasure / 2, SCREEN_HEIGHT / 2 + fontSize, fontSize, YELLOW);
}

void SnakeGame::RenderBoard()
{
	// black borders
	DrawRectangle(0, 0, SCREEN_WIDTH, BORDER_GAP.y / 2, BLACK); // top
	DrawRectangle(0, SCREEN_HEIGHT - BORDER_GAP.y / 2, SCREEN_WIDTH, BORDER_GAP.y / 2, BLACK); // bottom
	DrawRectangle(0, 0, BORDER_GAP.x / 2, SCREEN_HEIGHT, BLACK); // left
	DrawRectangle(SCREEN_WIDTH - BORDER_GAP.x / 2, 0, BORDER_GAP.x / 2, SCREEN_HEIGHT, BLACK); // right

	for (auto& row : grid)
	{
		for (Tile& tile : row)
		{
			tile.Render();
		}
	}
}

void SnakeGame::RenderAll()
{

	RenderBoard();
	_foodPickup->Render();
	_magicPickup->Render();
	_player.Render(_magicPickup->GetColor());

	if (_player.IsMagicControlled())
	{
		int temp = (int)(_player.magicTimer * 10);
		std::string timerDisplay = std::to_string(temp / 10) + "." + std::to_string(temp % 10);

		int fontSize = SCREEN_HEIGHT / 6;
		int textSize = MeasureText(timerDisplay.c_str(), fontSize);
		int textX = SCREEN_WIDTH / 2 - textSize / 2;
		int textY = SCREEN_HEIGHT / 2 - fontSize / 2;

		DrawText(timerDisplay.c_str(), textX, textY, fontSize, Color{ 255, 255, 255, 180 });
	}

	if (_state != State::play) { DrawRectangleV(Vector2{ 0,0 }, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT}, Color{69, 69, 69, 150 }); }
	if (_state == State::gameOver) { RenderBreakScreen("Game Over", RED); }
	if (_state == State::complete) { RenderBreakScreen("You Win!", GREEN); }
	if (_state == State::paused) { RenderBreakScreen("Game Paused", SKYBLUE); }
}


