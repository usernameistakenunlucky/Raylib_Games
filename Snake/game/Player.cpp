#include "Player.h"

bool Player::HitBorder()
{
	if (tail[0].position.x >= RIGHT_BOUNDS ||
		tail[0].position.x < LEFT_BOUNDS ||
		tail[0].position.y >= BOTTOM_BOUNDS ||
		tail[0].position.y < TOP_BOUNDS)
	{
		return true;
	}
	return false;
}

bool Player::HitSelf()
{
	for (int i = 1; i < tail.size(); i++)
	{
		if (tail[i].position == tail[0].position) { return true; }
	}
	return false;
}

bool Player::HitWall(std::vector<std::vector<Tile>>& grid)
{
	for (auto& row : grid)
	{
		for (auto& tile : row)
		{
			if (tile.blocked &&
				tile.position == tail[0].position - Vector2{ BORDER_GAP.x / 2, BORDER_GAP.y / 2 }) {
				return true;
			}
		}
	}
	return false;
}

void Player::Reset()
{
	magicTimer = 0.f;
	tail.clear();
}

// grid and pickupTile are needed for aStar during magic mode
void Player::Update(int frameCount, std::vector<std::vector<Tile>>& grid, Tile* pickupTile)
{
	if (IsMagicControlled()) magicTimer -= DELTA_TIME;

	if (frameCount % GAME_SPEED == 0)
	{
		if (magicTimer > 0.f)
		{
			// mark snake body tiles as blocked so aStar goes around them
			for (int i = 1; i < (int)tail.size(); i++)
			{
				int col = (int)((tail[i].position.x - BORDER_GAP.x / 2) / TILE_SIZE);
				int row = (int)((tail[i].position.y - BORDER_GAP.y / 2) / TILE_SIZE);
				if (row >= 0 && row < (int)grid.size() && col >= 0 && col < (int)grid[0].size())
				{
					grid[row][col].blocked = true;
				}
			}

			// find which tile the head is on
			int headCol = (int)((tail[0].position.x - BORDER_GAP.x / 2) / TILE_SIZE);
			int headRow = (int)((tail[0].position.y - BORDER_GAP.y / 2) / TILE_SIZE);
			Tile* startTile = &grid[headRow][headCol];

			// run A* — returns the first tile to step into
			Tile* nextTile = aStar.Search(grid, startTile, pickupTile);

			if (nextTile != nullptr)
			{
				// convert tile position back to a direction vector
				direction = Vector2
				{
					(float)(nextTile->gridX - startTile->gridX) * TILE_SIZE,
					(float)(nextTile->gridY - startTile->gridY) * TILE_SIZE
				};
			}
			// if no path found, keep current direction (snake keeps moving, may die — that's fine)

			// unblock the body tiles after the search
			for (int i = 1; i < (int)tail.size(); i++)
			{
				int col = (int)((tail[i].position.x - BORDER_GAP.x / 2) / TILE_SIZE);
				int row = (int)((tail[i].position.y - BORDER_GAP.y / 2) / TILE_SIZE);
				if (row >= 0 && row < (int)grid.size() && col >= 0 && col < (int)grid[0].size())
				{
					grid[row][col].blocked = false;
				}
			}
		}

		// move the snake (same for both manual and magic modes)
		for (int i = (int)tail.size() - 1; i > 0; i--)
		{
			tail[i].prevPosition = tail[i].position;
			tail[i].position = tail[i - 1].position;
			tail[i].Update();
		}
		tail[0].prevPosition = tail[0].position;
		tail[0].position += direction;
		tail[0].Update();
		canMove = true;
	}
}

void Player::Render(const Color& magicColor)
{
	for (int i = 0; i < (int)tail.size(); i++)
	{
		tail[i].Render();
		if (i == 0)
		{
			// draw tongue on head ----------------------------------------------------------------------------------------------------
			float baseLength = TILE_SIZE / 4.f;
			float baseWidth = baseLength / 3.f;
			float forkLength = TILE_SIZE / 8.f;
			float forkWidth = baseWidth / 2;

			float angle = 0.f;
			Vector2 headFront = { tail[0].position.x + TILE_SIZE / 2.f, tail[0].position.y + TILE_SIZE / 2.f };

			switch (tail[0].direction)
			{
			case 'U':
				angle = 270.f;
				headFront.y = tail[0].position.y;
				break;
			case 'D':
				angle = 90.f;
				headFront.y = tail[0].position.y + TILE_SIZE;
				break;
			case 'L':
				angle = 180.f;
				headFront.x = tail[0].position.x;
				break;
			case 'R':
				angle = 0.f;
				headFront.x = tail[0].position.x + TILE_SIZE;
				break;
			}

			// tongue base 
			DrawRectanglePro(Rectangle{ headFront.x, headFront.y, baseLength, baseWidth },
				Vector2{ 0.f, baseWidth / 2.f }, angle, RED);

			// right fork
			DrawRectanglePro(Rectangle{ headFront.x, headFront.y, forkLength, forkWidth },
				Vector2{ -baseLength, forkWidth / 2.f }, angle + forkWidth * 2, RED);

			// left fork
			DrawRectanglePro(
				Rectangle{ headFront.x, headFront.y, forkLength, forkWidth },
				Vector2{ -baseLength, forkWidth / 2.f }, angle - forkWidth * 2, RED);


			// draw eyes (purple if mind controlled) -------------------------------------------------------------------------------------
			float eyeOffset = TILE_SIZE / 4.f;
			float eyeRadius = TILE_SIZE / 8.f;
			float pupilRadius = eyeRadius / 2.f;
			float pupilShift = pupilRadius / 2.f;

			Vector2 eye1;
			Vector2 eye2;
			Vector2 pupil1;
			Vector2 pupil2;

			switch (tail[i].direction)
			{
			case 'U':
				eye1 = { tail[i].position.x + TILE_SIZE / 2.f - eyeOffset, tail[i].position.y + TILE_SIZE / 2.f };
				eye2 = { tail[i].position.x + TILE_SIZE / 2.f + eyeOffset, tail[i].position.y + TILE_SIZE / 2.f };
				pupil1 = { eye1.x, eye1.y - pupilShift };
				pupil2 = { eye2.x, eye2.y - pupilShift };
				break;
			case 'D':
				eye1 = { tail[i].position.x + TILE_SIZE / 2.f - eyeOffset, tail[i].position.y + TILE_SIZE / 2.f };
				eye2 = { tail[i].position.x + TILE_SIZE / 2.f + eyeOffset, tail[i].position.y + TILE_SIZE / 2.f };
				pupil1 = { eye1.x, eye1.y + pupilShift };
				pupil2 = { eye2.x, eye2.y + pupilShift };
				break;
			case 'L':
				eye1 = { tail[i].position.x + TILE_SIZE / 2.f, tail[i].position.y + TILE_SIZE / 2.f - eyeOffset };
				eye2 = { tail[i].position.x + TILE_SIZE / 2.f, tail[i].position.y + TILE_SIZE / 2.f + eyeOffset };
				pupil1 = { eye1.x - pupilShift, eye1.y };
				pupil2 = { eye2.x - pupilShift, eye2.y };
				break;
			case 'R':
			default:
				eye1 = { tail[i].position.x + TILE_SIZE / 2.f, tail[i].position.y + TILE_SIZE / 2.f - eyeOffset };
				eye2 = { tail[i].position.x + TILE_SIZE / 2.f, tail[i].position.y + TILE_SIZE / 2.f + eyeOffset };
				pupil1 = { eye1.x + pupilShift, eye1.y };
				pupil2 = { eye2.x + pupilShift, eye2.y };
				break;
			}

			if (magicTimer <= 0.f) // not mind controlled
			{
				DrawCircleV(eye1, eyeRadius, WHITE);
				DrawCircleV(eye2, eyeRadius, WHITE);
			}
			else // mind controlled eyes
			{
				DrawCircleV(eye1, eyeRadius, magicColor);
				DrawCircleV(eye2, eyeRadius, magicColor);
			}
			
			DrawCircleV(pupil1, pupilRadius, BLACK);
			DrawCircleV(pupil2, pupilRadius, BLACK);

		}
		else
		{
			// draw triangles on body ---------------------------------------------------------------------------------------------------
			switch (tail[i].direction)
			{
			case 'U': DrawTriangle(
				Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y },
				Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE },
				Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE }, DARKGREEN); break;

			case 'D': DrawTriangle(
				Vector2{ tail[i].position.x + TILE_SIZE / 2, tail[i].position.y + TILE_SIZE },
				Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y },
				Vector2{ tail[i].position.x, tail[i].position.y }, DARKGREEN); break;

			case 'R': DrawTriangle(
				Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE / 2 },
				Vector2{ tail[i].position.x, tail[i].position.y },
				Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE }, DARKGREEN); break;

			case 'L': DrawTriangle(
				Vector2{ tail[i].position.x, tail[i].position.y + TILE_SIZE / 2 },
				Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y + TILE_SIZE },
				Vector2{ tail[i].position.x + TILE_SIZE, tail[i].position.y }, DARKGREEN); break;
			}
		}
	}
}