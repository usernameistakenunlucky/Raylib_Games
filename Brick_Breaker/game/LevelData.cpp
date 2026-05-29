#include "WallBreaker.h"

void WallBreaker::InitializeLevels()
{
	//level 1 ( 2 rows) --------------------------------------------------------------------------------
	{
		Level level01;
		////////////////////////////////////////////////////////////////
		int rowsOfBricks = 2;
		int yOffset = 500;
		////////////////////////////////////////////////////////////////

		float totalSpaceForBricks = SCREEN_WIDTH - (BRICKS_PER_ROW * GAP + GAP);
		Vector2 brickSize = Vector2{ totalSpaceForBricks / BRICKS_PER_ROW, BRICK_HEIGHT };

		for (int row = 0; row < rowsOfBricks; row++)
		{
			for (int columb = 0; columb < BRICKS_PER_ROW; columb++)
			{
				float x = GAP + (brickSize.x + GAP) * columb;
				float y = GAP + (brickSize.y + GAP) * row;

				Rectangle rect = { x, y + yOffset, brickSize.x, brickSize.y };
				Brick brick = { RED_BRICK, rect };
				level01.AddBrick(brick);
			}
		}
		_levels.push_back(level01);
	}

	//level 2 (small circle) ------------------------------------------------------------------------------------
	{
		Level level02;
		////////////////////////////////////////////////////////////////
		int rowsOfBricks = 20;
		Vector2 circleCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.7 };
		float radius = SCREEN_WIDTH / 4;
		////////////////////////////////////////////////////////////////

		float totalSpaceForBricks = SCREEN_WIDTH - (BRICKS_PER_ROW * GAP + GAP);
		Vector2 brickSize = Vector2{ totalSpaceForBricks / BRICKS_PER_ROW, BRICK_HEIGHT };

		for (int row = 0; row < rowsOfBricks; row++)
		{
			for (int columb = 0; columb < BRICKS_PER_ROW; columb++)
			{
				float x = GAP + (brickSize.x + GAP) * columb;
				float y = GAP + (brickSize.y + GAP) * row;
				Vector2 position = { x,y };
				Vector2 center = {x + brickSize.x /2, y + brickSize.y /2};
				if (Vector2Distance(center, circleCenter) < radius)
				{
					Rectangle rect = { position.x, position.y, brickSize.x, brickSize.y };
					Brick brick = { RED_BRICK, rect };
					level02.AddBrick(brick);
				}
			}
		}
		_levels.push_back(level02);
	}

	//level 3 (big circle) ------------------------------------------------------------------------------------
	{
		Level level03;
		////////////////////////////////////////////////////////////////
		int rowsOfBricks = 20;
		Vector2 circleCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.7 };
		float radius = SCREEN_WIDTH / 3;
		////////////////////////////////////////////////////////////////

		float totalSpaceForBricks = SCREEN_WIDTH - (BRICKS_PER_ROW * GAP + GAP);
		Vector2 brickSize = Vector2{ totalSpaceForBricks / BRICKS_PER_ROW, BRICK_HEIGHT };

		for (int row = 0; row < rowsOfBricks; row++)
		{
			for (int columb = 0; columb < BRICKS_PER_ROW; columb++)
			{
				float x = GAP + (brickSize.x + GAP) * columb;
				float y = GAP + (brickSize.y + GAP) * row;
				Vector2 position = { x,y };
				Vector2 center = { x + brickSize.x / 2, y + brickSize.y / 2 };
				if (Vector2Distance(center, circleCenter) < radius)
				{
					Rectangle rect = { position.x, position.y, brickSize.x, brickSize.y };
					Brick brick = { RED_BRICK, rect };
					level03.AddBrick(brick);
				}
			}
		}
		_levels.push_back(level03);
	}

}