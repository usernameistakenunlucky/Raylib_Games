#pragma once
#include <raylib.h>


// tiles
constexpr int TILE_SIZE = 110;

// screen
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 960;
constexpr int GAME_SPEED = 10;

// grid
constexpr Vector2 BORDER_GAP = Vector2{ SCREEN_WIDTH % TILE_SIZE, SCREEN_HEIGHT % TILE_SIZE };

constexpr int RIGHT_BOUNDS	= SCREEN_WIDTH - BORDER_GAP.x / 2;
constexpr int LEFT_BOUNDS	= BORDER_GAP.x / 2;
constexpr int BOTTOM_BOUNDS = SCREEN_HEIGHT - BORDER_GAP.y / 2;
constexpr int TOP_BOUNDS	= BORDER_GAP.y / 2;





