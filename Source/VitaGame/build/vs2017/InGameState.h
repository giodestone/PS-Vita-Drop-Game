#pragma once
#include "GameState.h"
class InGameState :
	public GameState
{
public:
	/// <summary>
	/// Game state which holds details for loading into the game.
	/// </summary>
	InGameState();
	~InGameState();

	void LoadIn() override;
};