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
	int nStartPoison = 5;
	// Game Objects //
	Board board;
	Snake snek;
	Goal goal;
	
	// Timers and Counters //
	FrameTimer ft;
	static constexpr float snekMovePeriodMin = .000000000006;
	static constexpr float snekSpeedupFactor = 0.01f;

	float snekMovePeriod = 0.4f;
	float snekMoveCounter = 0.0f;
	float obstacle_spawn_counter_ = 0.0f;
	float poison_spawn_period_ = 5.0f;


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