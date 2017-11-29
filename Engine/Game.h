/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Location.h"
#include "Snake.h"
#include "Goal.h"
#include "FrameTimer.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */

	std::mt19937 rng;
	// Game Objects //
	Board board;
	Snake snek;
	Goal goal;
	
	// Timers and Counters //
	FrameTimer ft;
	static constexpr int snekMovePeriodMin = 4;
	float snekMovePeriod = 0.75f;
	float snekMoveCounter = 0.0f;
	float snekSpeedupPeriod = 10.0f;
	float snekSpeedupCounter = 0.0;

	// Flags //
	bool suppressGrowth = false;
	bool GameIsOver = false;
	bool GameIsStarted = false;

	// Locations //
	Location snekStart = { 0, 0 };
	Location delta_loc = { 0, 1};


	// ETC //
	
	/********************************/
};