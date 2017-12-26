#pragma once

#include "Board.h"
#include "Location.h"
#include "Colors.h"
#include <vector>

class Snake
{
private:
	class Segment
	{
	public:
		Segment(const Location& in_loc);
		Segment(Color c_in);
		void Follow(const Segment& next);
		void Draw(Board& board) const;
		void MoveBy(const Location& delta_loc);
		Location GetLocation() const;
		void set_loc(const Location& in_loc);
	private:
		Color snakeColors[10] = { Colors::White, Colors::Gray, Colors::LightGray, Colors::Red, Colors::Green, Colors::Blue, Colors::Yellow, Colors::Cyan, Colors::Magenta, Colors::AliceBlue };
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	
	void MoveBy(const Location& delta_loc);
	void GrowAndMoveBy(const Location& delta_loc);
	void Draw(Board& board) const;
	Location GetNextHeadLocation(const Location & delta_loc) const;
	bool IsInTileExceptEnd(const Location & target) const;
	bool IsInTile(const Location & target) const;
	int getLength() const;
	void reset();

private:
	
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nBodyColors = 4;
	static constexpr Color bodyColors[nBodyColors] = {
		{ 10,100,32 },
		{ 10,130,48 },
		{ 18,160,48 },
		{ 10,130,48 }
	};
	std::vector<Segment> segments;
};