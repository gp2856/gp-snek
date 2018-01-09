#pragma once

#include "Location.h"
#include "Graphics.h"
#include "Colors.h"
#include "GameSettings.h"
#include <random>

class Board
{
public:
	enum class TileTypes
	{
		kEmpty,
		kObstacle,
		kFood,
		kPoison
	};
public:
	Board(Graphics& gfx, const GameSettings& config);
	void DrawCell(const Location& loc, const Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location & loc) const;
	TileTypes get_tile_type(const Location& loc) const;
	const Location get_food_loc() const;
	void set_random_tile_(std::mt19937 rng, const class Snake& snake, const TileTypes type);
	void set_tile_(const Location& loc, const TileTypes type);
	void clear_tile(const Location& loc);
	void move_food(const std::mt19937 rng, const class Snake& snake);
	void init_poison(std::mt19937 rng, const class Snake& snake, const int count);
	void draw_tiles();
private:
	Graphics & gfx;
	int dimension;
	int width;
	int height;
	static constexpr int padding = 5;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 2;
	static constexpr Color borderColor = Colors::AliceBlue;
	static constexpr Color obstacle_color = Colors::Gray;
	static constexpr Color poison_color = Colors::Cyan;
	static constexpr Color goal_color = Colors::Red;
	int x = 75;
	int y = 35;
	TileTypes *tiles_;
	
};