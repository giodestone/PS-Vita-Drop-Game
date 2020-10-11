#pragma once
#include "GameState.h"
class InstructionsState :
	public GameState
{
public:
	/// <summary>
	/// Instructions for loading into and out of the instructions menu.
	/// </summary>
	InstructionsState();
	~InstructionsState();

	void LoadIn() override;
};

