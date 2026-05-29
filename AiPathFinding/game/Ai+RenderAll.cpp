#include "Ai.h"

void Ai::RenderAll()
{
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Draw();
		}
	}
}