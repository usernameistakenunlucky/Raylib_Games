#pragma once
#include <raylib.h>
#include <string>

inline float DELTA_TIME = 0.f;

// tiles
constexpr int TILE_SIZE = 120;
constexpr Color TILE_COLOR = GRAY;

// screen
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = SCREEN_WIDTH * 0.5625; // for 16/9 aspect on any width
constexpr int GAME_SPEED = 10;

// grid
constexpr Vector2 BORDER_GAP = Vector2{ SCREEN_WIDTH % TILE_SIZE, SCREEN_HEIGHT % TILE_SIZE };
constexpr int COLUMNS = (SCREEN_WIDTH - BORDER_GAP.x) / TILE_SIZE;
constexpr int ROWS = (SCREEN_HEIGHT - BORDER_GAP.y) / TILE_SIZE;

constexpr int RIGHT_BOUNDS = SCREEN_WIDTH - BORDER_GAP.x / 2;
constexpr int LEFT_BOUNDS = BORDER_GAP.x / 2;
constexpr int BOTTOM_BOUNDS = SCREEN_HEIGHT - BORDER_GAP.y / 2;
constexpr int TOP_BOUNDS = BORDER_GAP.y / 2;

// pickups
constexpr float MAGIC_DURATION = 10.f;


inline void DrawRectangleLinesV(Vector2 position, Vector2 size, float thickness, Color color)
{
	DrawRectangleLinesEx(Rectangle{ position.x, position.y, size.x, size.y }, thickness, color);
}

inline void DrawCherries(Vector2 position)
{
	Color cherryColor = Color{ (unsigned char)(RED.r * 0.8), (unsigned char)(RED.g * 0.8), (unsigned char)(RED.b * 0.8), 255 };
	int radius = TILE_SIZE / 4.5;


	Vector2 cherry1Pos = { position.x + TILE_SIZE / 2.f - radius * 0.9f, position.y + TILE_SIZE / 2.f + radius * 0.5f };
	Vector2 cherry2Pos = { cherry1Pos.x + (radius * 2 * 0.9), cherry1Pos.y + (radius * 2 * 0.1) };

	DrawCircleV(cherry1Pos, radius * 1.1, Color{ (unsigned char)(cherryColor.r * 0.8), (unsigned char)(cherryColor.g * 0.8), (unsigned char)(cherryColor.b * 0.8), 255 });
	DrawCircleV(cherry1Pos, radius, cherryColor);
	DrawCircleSector({ cherry1Pos.x + radius / 10, cherry1Pos.y }, radius * 0.8, 110, 250, 36, WHITE);
	DrawCircleSector({ cherry1Pos.x + radius / 3, cherry1Pos.y }, radius * 0.9, 110, 250, 36, cherryColor);

	DrawCircleV(cherry2Pos, radius * 1.1, Color{ (unsigned char)(cherryColor.r * 0.8), (unsigned char)(cherryColor.g * 0.8), (unsigned char)(cherryColor.b * 0.8), 255 });
	DrawCircleV(cherry2Pos, radius, cherryColor);
	DrawCircleSector({ cherry2Pos.x + radius / 10, cherry2Pos.y }, radius * 0.8, 110, 250, 36, WHITE);
	DrawCircleSector({ cherry2Pos.x + radius / 3, cherry2Pos.y }, radius * 0.9, 110, 250, 36, cherryColor);

	Vector2 stem1Pos = { cherry1Pos.x, cherry1Pos.y - (radius * 0.9f) };
	Vector2 stem2Pos = { cherry2Pos.x, cherry2Pos.y - (radius * 0.9f) };
	Vector2 stemsMeet = { cherry1Pos.x + radius * 1.5, cherry1Pos.y - radius * 2 };
	DrawCircleV(stem1Pos, radius / 7, DARKBROWN);
	DrawCircleV(stem2Pos, radius / 7, DARKBROWN);
	DrawLineEx(stem1Pos, stemsMeet, radius / 5, DARKBROWN);
	DrawLineEx(stem2Pos, stemsMeet, radius / 5, DARKBROWN);
	Color leafColor = Color{ (unsigned char)(GREEN.r * 0.8), (unsigned char)(GREEN.g * 0.8), (unsigned char)(GREEN.b * 0.8), 255 };
	int leafRadius = radius / 2;
	DrawCircleV(stemsMeet, leafRadius, leafColor);
	DrawTriangle(Vector2{ stemsMeet.x, stemsMeet.y - leafRadius }, Vector2{ stemsMeet.x, stemsMeet.y + leafRadius }, Vector2{ stemsMeet.x + radius * 2, stemsMeet.y }, leafColor);
	DrawLineEx(Vector2{ stemsMeet.x - leafRadius, stemsMeet.y }, Vector2{ stemsMeet.x + radius * 2, stemsMeet.y }, radius / 10, DARKGREEN);
}



// for getting the asset path on any pc this app is run on:
inline std::string StripSuffix(const std::string& path, const std::string& suffix)
{
	size_t pos = path.rfind(suffix);
	if (pos != std::string::npos)
	{
		return path.substr(0, pos);
	}
	return path; // suffix not found, return as-is
}
inline std::string GetAssetPath()
{
	std::string appDir = GetApplicationDirectory();
	appDir = StripSuffix(appDir, "x64\\Debug\\");
	return appDir + "assets\\";
}
inline const std::string ASSET_PATH = GetAssetPath();
//_texture = LoadTexture(std::string(ASSET_PATH + "FileName.png").c_str());