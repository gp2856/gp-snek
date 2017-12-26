#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;
	gfx.DrawRectDim(loc.x * dimension + off_x + cellPadding, loc.y * dimension + off_y + cellPadding, dimension - (cellPadding * 2), dimension - (cellPadding * 2), c);
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;

	const int bottom = top + (borderWidth + borderPadding) * 2 + (height * dimension);
	const int right = left + (borderWidth + borderPadding) * 2 + (width * dimension);

	// top
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	// left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);
	// right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);
	// bottom
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);

}



int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

Board::TileTypes Board::get_tile_type(const Location & loc) const
{
	return tiles_[loc.x + loc.y * width];
}

const Location Board::get_food_loc() const
{
	for (auto y = 0; y < height; y++)
	{
		for (auto x = 0; x < width; x++)
		{
			if(get_tile_type({x,y}) == TileTypes::kFood)
			{
				return { x,y };
			}
		}
	}
	return { 0,0 };
}

void Board::set_random_tile_(std::mt19937 rng, const Snake & snake, const TileTypes type)
{
	const std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	const std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || get_tile_type(newLoc) != TileTypes::kEmpty);

	tiles_[newLoc.x + newLoc.y * width] = type;
}

void Board::set_tile_(const Location& loc, const TileTypes type)
{
	tiles_[loc.x + loc.y * width] = type;
}

void Board::clear_tile(const Location & loc)
{
	tiles_[loc.x + loc.y * width] = TileTypes::kEmpty;
}

void Board::move_food(const std::mt19937 rng, const Snake& snake)
{
	for (auto y = 0; y < height; y++)
	{
		for (auto x = 0; x < width; x++)
		{
			if (get_tile_type({ x,y }) == TileTypes::kFood)
			{
				clear_tile({ x,y });
				set_random_tile_(rng, snake, TileTypes::kFood);
			}
		}
	}
}

void Board::init_poison(std::mt19937 rng, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);


	for (auto i = 0; i <= n_poison_; i++)
	{
		const Location newLoc = { xDist(rng), yDist(rng) };
		if (get_tile_type(newLoc) == TileTypes::kEmpty && !snake.IsInTile(newLoc))
		{
			tiles_[newLoc.x + newLoc.y * width] = TileTypes::kPoison;
		}
	}
}

void Board::draw_tiles()
{
	for (auto y = 0; y < height; y++)
	{
		for (auto x = 0; x < width; x++)
		{
			switch(get_tile_type({x,y}))
			{
			case TileTypes::kEmpty:
				break;
			case TileTypes::kFood:
				DrawCell({ x,y }, goal_color);
				break;
			case TileTypes::kObstacle:
				DrawCell({ x,y }, obstacle_color);
				break;
			case TileTypes::kPoison:
				DrawCell({ x,y }, poison_color);
				break;
			default:
				break;
			}
		}
	}
}
