#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snek, Color in_c)
{
	c = in_c;
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937 & rng,const Board & brd, const Snake & snek)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || brd.get_tile_type(newLoc) != 0);

	loc = newLoc;
}

void Goal::Draw(Board & brd) 
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
