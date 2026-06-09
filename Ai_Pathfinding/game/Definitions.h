#pragma once

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 1000;
inline float DELTA_TIME = 0.f;

constexpr float PERCENT_BLOCKED = 0.25;
constexpr int COLUMNS = 20;
constexpr int ROWS = 20;
constexpr int NODE_SIZE = 50; // w/h of each tile
constexpr int DARKEN_RATE = 30; // speed at which it darkens failed paths

constexpr int NODE_ANIM_TIME = 5;
constexpr int NODE_ANIM_SPEED = 12;

constexpr Color PATH_COLOR = Color{255, 203, 0, 255};

constexpr Color BFS_COLOR = Color{ 135, 206, 235, 255 }; // light blue
constexpr Color DFS_COLOR = Color{ 200, 122, 255, 255 }; // purple 
constexpr Color DJIKSTRA_COLOR = Color{ 6, 64, 43, 255 }; // dark green 
constexpr Color ASTAR_COLOR = PINK; // pink

enum class AiState
{
	waiting,

	BFS,
	traceBFS,

	DFS,
	traceDFS,

	djikstra,
	traceDjikstra,

	aStar,
	traceAStar,
};

enum class NodeRenderState
{
	growing,
	shrinking,
	still,
};

inline void DrawRectangleLinesV(Vector2 position, Vector2 size, Color color)
{
	DrawRectangleLines(position.x, position.y, size.x, size.y, color);
}