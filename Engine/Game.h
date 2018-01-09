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
#include "SoundEffect.h"
#include "GameSettings.h"
#include <random>
#include <string>

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
	void lose_a_life();
	bool out_of_lives();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 rng;
	
	
	int n_poison;
	// Game Objects //
	GameSettings config;
	Board board;
	Snake snek;	
	
	// Timers and Counters //
	FrameTimer ft;
	static constexpr float snekMovePeriodMin = .000000000006;
	static constexpr float snekSpeedupFactor = 0.01f;

	float snekMovePeriod = 0.4f;
	float snekMoveCounter = 0.0f;
	float obstacle_spawn_counter_ = 0.0f;
	float poison_spawn_period_ = 5.0f;

	static constexpr int n_lives_ = 3;

	// Flags //
	bool suppressGrowth = false;
	bool GameIsOver = false;
	bool GameIsStarted = false;
	bool lives_[n_lives_] = { true };

	// Locations //
	Location snekStart = { 0, 0 };
	Location delta_loc = { 0, 0};


	// ETC //
	
	std::string config_path = "config.txt";
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	SoundEffect sfxSlither = SoundEffect({ L"Sounds\\Slither0.wav",L"Sounds\\Slither1.wav",L"Sounds\\Slither2.wav" });
	Sound snd_music_ = Sound(L"Sounds\\Music_Loop.wav", Sound::LoopType::AutoFullSound);
	Sound snd_title_ = Sound(L"Sounds\\Title.wav");
	Sound snd_fart_ = Sound(L"Sounds\\Fart.wav");
	/********************************/
};