#include "Snake.h"
#include <assert.h>

Snake::Segment::Segment(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

Snake::Segment::Segment(Color c_in)
{
	c = c_in;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}


void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert((abs(delta_loc.x) + abs(delta_loc.y)) == 1);
	loc.Add(delta_loc);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}

void Snake::Segment::set_loc(const Location& in_loc)
{
	loc = in_loc;
}


Snake::Snake(const Location & loc)
{
	segments.emplace_back(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (size_t i = segments.size() - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i-1]);
	}
	segments.front().MoveBy(delta_loc);
}

void Snake::GrowAndMoveBy(const Location& delta_loc)
{
	segments.emplace_back(bodyColors[segments.size() % nBodyColors]);
	MoveBy(delta_loc);
}

void Snake::Draw(Board & board) const
{
	for (const auto& s: segments)
	{
		s.Draw(board);
	}
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);

	return l;
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for (size_t i = 0; i < segments.size() - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location & target) const
{
	for (const auto& s: segments)
	{
		if (s.GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::getLength() const
{
	return (int)segments.size();
}

void Snake::reset(const Board& board)
{
	segments.clear();
	segments.emplace_back(headColor);
	segments[0].set_loc({ board.GetGridWidth() / 2, board.GetGridHeight() / 2 });
}
