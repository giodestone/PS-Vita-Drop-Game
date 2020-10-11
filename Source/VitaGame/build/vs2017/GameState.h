#pragma once
#include "GameStateEnum.h"
/// <summary>
/// Holds the load in and load out functions for the relevant GameState.
/// </summary>
class GameState
{
	GAME_STATE_ENUM gameStateAssociatedWith;
public:
	/// <summary>
	/// Responsible for loading and cleaning up anything for the GameState.
	/// </summary>
	/// <param name="gameStateAssociatedWith">Which gamestate this loading code is associated with.</param>
	GameState(GAME_STATE_ENUM gameStateAssociatedWith);
	virtual ~GameState();

	/// <summary>
	/// What to do when going into scene.
	/// </summary>
	virtual void LoadIn();

	/// <summary>
	/// What to do when leaving scene.
	/// </summary>
	virtual void CleanUp();

	inline GAME_STATE_ENUM GetStateAssociatedWith() const { return gameStateAssociatedWith; }
};

