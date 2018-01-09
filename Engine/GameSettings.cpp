#include "GameSettings.h"
#include <fstream>

GameSettings::GameSettings(const std::string & filename)
{
	std::ifstream in(filename);

	for(std::string line; std::getline(in, line);)
	{
		if(line == "[Tile Size]")
		{
			in >> tile_size_;
		}
		else if(line == "[Board Dimensions]")
		{
			in >> board_width_ >> board_height_;
		}
		else if(line == "[Number of Poison]")
		{
			in >> n_poison_;
		}
		else if(line == "[Number of Food]")
		{
			in >> n_food_;
		}
		else if (line == "[Snake Speedup Period]")
		{
			in >> snake_speedup_period_;
		}
	}
}

int GameSettings::get_tile_size() const
{
	return tile_size_;
}

int GameSettings::get_board_width() const
{
	return board_width_;
}

int GameSettings::get_board_height() const
{
	return board_height_;
}

int GameSettings::get_n_poison() const
{
	return n_poison_;
}

int GameSettings::get_n_food() const
{
	return n_food_;
}

float GameSettings::get_snake_speedup_period() const
{
	return snake_speedup_period_;
}
