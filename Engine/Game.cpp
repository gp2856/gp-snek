/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	snek({ Board::width/2, Board::height/2 }),
	rng(std::random_device()())
{
	std::fill_n(lives_, n_lives_, true);
	board.init_poison(rng, snek);
	board.set_random_tile_(rng, snek, Board::TileTypes::kFood);
	snd_title_.Play(1.0f, 1.0f);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	const float dt = ft.Mark();
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		snd_music_.Play(1.0f, 0.6f);
		GameIsStarted = true;
	}
	if (GameIsStarted)
	{
		if (!GameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1,0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1,0 };
			}

			

			snekMoveCounter += dt;
			if (snekMoveCounter >= snekMovePeriod)
			{
				snekMoveCounter = 0;
				const float dt = ft.Mark();
				const Location next = snek.GetNextHeadLocation(delta_loc);

				
				if (!board.IsInsideBoard(snek.GetNextHeadLocation(delta_loc)) ||
					snek.IsInTileExceptEnd(next) ||
					board.get_tile_type(next) == Board::TileTypes::kObstacle)
				{
					lose_a_life();
					snd_fart_.Play();
					if (out_of_lives())
					{
						GameIsOver = true;
						snd_music_.StopAll();
					}
				}
				else
				{
					const bool eating = next == board.get_food_loc();
					if (eating)
					{
						
						snek.GrowAndMoveBy(delta_loc);
						board.move_food(rng, snek);
						sfxEat.Play(rng, 0.8f);
					}

					if (board.get_tile_type(next) == Board::TileTypes::kPoison)
					{
						snekMovePeriod = std::max(snekMovePeriod - dt * snekSpeedupFactor, snekMovePeriodMin);
						board.clear_tile(next);
					}
					
					if (board.IsInsideBoard(snek.GetNextHeadLocation(delta_loc)))
					{
						snek.MoveBy(delta_loc);
					}
					else
					{
						GameIsOver = true;
					}
					sfxSlither.Play(rng, 0.8f);

				}
			}	

			snekMovePeriod = std::max(snekMovePeriod - dt * snekSpeedupFactor, snekMovePeriodMin);

			obstacle_spawn_counter_ += dt;
			if (obstacle_spawn_counter_ >= poison_spawn_period_)
			{
				obstacle_spawn_counter_ = 0;
				board.set_random_tile_(rng, snek, Board::TileTypes::kObstacle);
			}
		}
	}
}

void Game::lose_a_life()
{
	for (auto i = 0; i < n_lives_; i++)
	{
		if (lives_[i])
		{
			lives_[i] = false;
			break;
		}
	}
}

bool Game::out_of_lives()
{
	return !lives_[n_lives_ - 1];
}

void Game::ComposeFrame()
{
	if (!GameIsStarted)
	{
		SpriteCodex::DrawTitle((Graphics::ScreenWidth / 2) - (214 / 2), (Graphics::ScreenHeight / 2) - (161 / 2), gfx);
	}
	if (GameIsStarted)
	{
		for (auto i = 0; i < n_lives_; i++)
		{
			if (lives_[i])
			{
				SpriteCodex::DrawLife(10, 50 + 20 * i, gfx);
			}
		}
		snek.Draw(board);
		board.DrawBorder();
		board.draw_tiles();
		
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver((Graphics::ScreenWidth / 2) - (83 / 2), (Graphics::ScreenHeight / 2) - (63 / 2), gfx);
		}
	}

}
