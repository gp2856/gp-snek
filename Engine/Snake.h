#pragma once

#include "Board.h"
#include "Location.h"
#include "Colors.h"
#include <list>

class Snake
{
private:
	class Segment
	{
	public:
		void Follow(const Segment& next);
		void Draw(Board& board);
		void InitHead(const Location& in_loc);
		void InitBody(int nSegs);
		void MoveBy(const Location& delta_loc);
		Location GetLocation() const;
	private:
		Color snakeColors[10] = { Colors::White, Colors::Gray, Colors::LightGray, Colors::Red, Colors::Green, Colors::Blue, Colors::Yellow, Colors::Cyan, Colors::Magenta, Colors::AliceBlue };
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& board);
	Location GetNextHeadLocation(const Location & delta_loc) const;
	bool IsInTileExceptEnd(const Location & target) const;
	bool IsInTile(const Location & target) const;
	int getLength();

private:
	
	static constexpr Color HeadColor = Colors::White;
	static constexpr Color BodyColor = Colors::White;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};