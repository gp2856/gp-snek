#pragma once

#include "Location.h"
#include "Graphics.h"
#include "Colors.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, const Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location & loc) const;
	int get_tile_type(const Location& loc) const;
	void set_tile(std::mt19937 rng, const class Snake& snake, const class Goal& goal, const int type);
	void draw_special_tiles();
private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int padding = 5;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 2;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacle_color = Colors::Gray;
	static constexpr Color poison_color = Colors::Magenta;
	static constexpr int x = ((Graphics::ScreenWidth / 2) - (width * dimension)/2);
	static constexpr int y = ((Graphics::ScreenHeight / 2) - (height * dimension)/2);
	// 0: empty, 1: obstacle, 2: poison
	int tile_type_[width * height] = { 0 };
	Graphics& gfx;
};