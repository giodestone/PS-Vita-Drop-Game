#pragma once
#include "GameState.h"
class GameOverState :
	public GameState
{
public:
	/// <summary>
	/// State which holds load in/load out info for the game over screen.
	/// </summary>
	GameOverState();
	~GameOverState();

	void LoadIn() override;
	void CleanUp() override;
};

