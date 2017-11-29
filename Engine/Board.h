#pragma once

#include "Location.h"
#include "Graphics.h"
#include "Colors.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(Location& loc, const Color c);
	void DrawBorder();
	void ClampCell(Location& loc);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location & loc) const;

private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int padding = 5;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 2;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int x = ((Graphics::ScreenWidth / 2) - (width * dimension)/2);
	static constexpr int y = ((Graphics::ScreenHeight / 2) - (height * dimension)/2);
	Graphics& gfx;
};