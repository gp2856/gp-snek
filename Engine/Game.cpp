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
	snek({ 1, 1 }),
	rng(std::random_device()()),
	goal(rng, board, snek)
{
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
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
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


			snekMoveCounter++;

			if (snekMoveCounter == snekMovePeriod)
			{
				snekMoveCounter = 0;
				Location next = snek.GetNextHeadLocation(delta_loc);

				/*if (next == goal.GetLocation())
				{
					snek.GrowAndMoveBy(delta_loc);
				}*/
				if (!board.IsInsideBoard(snek.GetNextHeadLocation(delta_loc)) ||
					snek.IsInTileExceptEnd(next))
				{
					GameIsOver = true;
				}
				else
				{
					const bool eating = next == goal.GetLocation();
					if (eating)
					{
						snek.GrowAndMoveBy(delta_loc);
						if (eating)
						{
							goal.Respawn(rng, board, snek);
							snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
						}
					}
					snek.MoveBy(delta_loc);

				}
			}
			++snekSpeedupCounter;
			
		}
	}
}

void Game::ComposeFrame()
{
	if (!GameIsStarted)
	{
		SpriteCodex::DrawTitle((Graphics::ScreenWidth / 2) - (214 / 2), (Graphics::ScreenHeight / 2) - (161 / 2), gfx);
	}
	if (GameIsStarted)
	{
		snek.Draw(board);
		goal.Draw(board);
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver((Graphics::ScreenWidth / 2) - (83 / 2), (Graphics::ScreenHeight / 2) - (63 / 2), gfx);
		}

		board.DrawBorder();
	}

}
