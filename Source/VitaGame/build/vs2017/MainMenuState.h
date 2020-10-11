#pragma once
#include <graphics/texture.h>

#include "GameState.h"

class MainMenuState :
	public GameState
{
public:
	/// <summary>
	/// Instructions for loading into and out of the main menu.
	/// </summary>
	MainMenuState();
	~MainMenuState();

	void LoadIn() override;
	void CleanUp() override;

private:
	/// <summary>
	/// Add a button at a specific poistion.
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="texture"></param>
	/// <param name="stateToChangeTo"></param>
	void addButton(float pos, gef::Texture* texture, GAME_STATE_ENUM stateToChangeTo);
};

