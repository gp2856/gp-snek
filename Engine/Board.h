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
	bool check_for_obstacle(const Location& loc) const;
	void set_obstacle(std::mt19937 rng, const class Snake& snake, const class Goal& goal);
	void draw_obstacles();
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
	static constexpr int x = ((Graphics::ScreenWidth / 2) - (width * dimension)/2);
	static constexpr int y = ((Graphics::ScreenHeight / 2) - (height * dimension)/2);
	bool has_obstacle_[width * height] = { true };
	Graphics& gfx;
};