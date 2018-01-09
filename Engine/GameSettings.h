#pragma once

#include <string>

class GameSettings
{
public:
	GameSettings(const std::string& filename);
	int get_tile_size() const;
	int get_board_width() const;
	int get_board_height() const;
	int get_n_poison() const;
	int get_n_food() const;
	float get_snake_speedup_period() const;
private:
	int tile_size_;
	int board_width_;
	int board_height_;
	int n_poison_;
	int n_food_;
	float snake_speedup_period_;
};