#pragma once
#include "GameState.h"
class OptionsState :
	public GameState
{
public:
	/// <summary>
	/// Instructions for loading into and out of the options menu.
	/// </summary>
	OptionsState();
	~OptionsState();

	void LoadIn() override;
};

