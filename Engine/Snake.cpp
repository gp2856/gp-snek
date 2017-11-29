#include "Snake.h"
#include <assert.h>

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & board)
{
	board.DrawCell(loc, c);
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody(int nSegs)
{
	
	c = snakeColors[nSegs % 10];
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


Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments; i > 0; i--)
	{
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	assert(nSegments <= nSegmentsMax);
	segments[nSegments].InitBody(nSegments);
	nSegments++;
}

void Snake::Draw(Board & board)
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(board);
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
	for (int i = 0; i < nSegments - 1; i++)
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
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::getLength()
{
	return nSegments;
}
