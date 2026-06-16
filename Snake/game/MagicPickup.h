#pragma once
#include "Pickup.h"

class MagicPickup : public Pickup
{
private:
	//for colors
	float _colorHue = 0.0f;          // 0–360 degrees
	float _colorSpeed = 150.0f;      // degrees per second — tweak for faster/slower


public:

	MagicPickup(const Vector2& freePostion)
		: Pickup(freePostion)
	{
		value = 200;
		color = PURPLE;
	}

	void Effect(Player& player) override
	{
		// activate AStar for 10 seconds and disable user input... + make eyes purple?
		player.SetMagic(GetRandomValue(MAGIC_DURATION / 2, MAGIC_DURATION));
		player.score += value;
	}
	void Update() override
	{
		_colorHue += _colorSpeed * GetFrameTime();
		if (_colorHue >= 360.0f) { _colorHue -= 360.0f; }

		color = ColorFromHSV(_colorHue, 1.0f, 1.0f);
	}
	void Render() override
	{
		if (!active) { return; }

		Vector2 centerPos = Vector2{ position.x + TILE_SIZE / 2, position.y + TILE_SIZE / 2 };
		DrawCircleV(centerPos, TILE_SIZE / 2, color);
		DrawCircleV(centerPos, TILE_SIZE / 2.4, GetColor());
		//draw stem
		DrawLineEx(Vector2{ centerPos.x, position.y }, Vector2{ centerPos.x, position.y + TILE_SIZE / 4 }, 12.f, BROWN);
	}

	Color GetColor() const override
	{
		float purpleHue = 270.0f + sinf(_colorHue * DEG2RAD) * 40.0f; // oscillates between 230–310

		return ColorFromHSV(purpleHue, 0.9f, 1.0f);
	}
};