#include "WallBreaker.h"
#include <raymath.h>
#include <ostream>
#include <string>

WallBreaker::WallBreaker()
{

}

void WallBreaker::Start()
{
	InitializePlayer();
	InitializeLevels();
	InitializeBall();
}

void WallBreaker::Main()
{
	Start();

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "WallBreaker Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
		DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, {50,50,50,255}, {100,100,100,255});



		UpdateAll();
		RenderAll();

		EndDrawing();
	}
	CloseWindow();
}

void WallBreaker::InitializePlayer()
{
	Vector2 playerSize = Vector2{ 200,32 };
	Vector2 playerStartPosition = Vector2{
		(SCREEN_WIDTH / 2) - (playerSize.x / 2),
		SCREEN_HEIGHT - playerSize.y - BOTTOM_GAP };

	_player = new Player(playerStartPosition, playerSize);
}
//void WallBreaker::InitializeLevels() -> in LevelData.cpp
void WallBreaker::InitializeBall()
{
	Vector2 ballPosition = Vector2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT - (BOTTOM_GAP + _player->GetSize().y + BALL_RADIUS) };
	_ball = { ballPosition };
}

void WallBreaker::CheckIfLevelComplete()
{
	for (const auto& brick : CurrentLevel().GetBricks())
	{
		if (brick.IsActive()) { return; }
	}
	NextLevel();
}

void WallBreaker::UpdateAll()
{
	////////////////////////////////////  Cheats: //////////////////////////////////////////
	if (IsKeyPressed(KEY_EQUAL)) { NextLevel(); }


	////////////////////////////////////////////////////////////////////////////////////////

	UiInput input = _ui.Update(_state);
	if /**/ (input == UiInput::Restart) { _state = State::Play; Restart(); }
	else if (input == UiInput::Unpause) { _state = State::Play; }

	if (_player->GetLives() < 1) { _state = State::GameOver; }	// check if player dead
	if (IsKeyDown(KEY_P)) /*  */ { _state = State::Paused; }	// check for pause input

	CheckIfLevelComplete();

	if (_state == State::Play) // update objects if in play:
	{
		for (Brick brick : CurrentLevel().GetBricks()) { brick.Update(); }
		_player->Update();
		_ball.Update(CurrentLevel().GetBricks(), *_player, _score, _currentLevel);
	}
}

void WallBreaker::Restart()
{
	_currentLevel = 1;
	_score = 0;
	for (Brick& brick : CurrentLevel().GetBricks()) { brick.Reset(); }
	_player->ResetPos();
	_player->ResetLives();
	_ball.Reset();
}

void WallBreaker::NextLevel()
{
	_currentLevel++;
	if (_currentLevel > _levels.size())
	{
		_state = State::Win;
		return;
	}

	for (auto& level : _levels) { level.Reset(); }
	_player->ResetPos();
	_ball.Reset();
}

void WallBreaker::RenderAll()
{
	for (const Brick& brick : CurrentLevel().GetBricks()) { brick.Render(); }
	_player->Render();
	_ball.Render();
	_ui.Render(*_player, _score, _currentLevel, _state);
}


