#pragma once
#include "Pickup.h"

class FoodPickup : public Pickup
{
private:



public:

	FoodPickup(const Vector2& freePostion)
		: Pickup(freePostion)
	{
		value = 25;
		color = ORANGE;
	}

	void Effect(Player& player) override
	{
		player.score += value;
		player.AddPiece();
	}

	void Render() override
	{
		DrawCherries(position);
	}
};