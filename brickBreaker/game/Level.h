#pragma once
#include <vector>
#include "Brick.h"

class Level
{
private:
	std::vector<Brick> _bricks;


public:
	Level()
	{

	}

	std::vector<Brick>& GetBricks() { return _bricks; }

	void AddBrick(const Brick& brick) { _bricks.push_back(brick); }

	void Reset()
	{
		for (Brick& brick : _bricks) { brick.Reset(); }
	}
};