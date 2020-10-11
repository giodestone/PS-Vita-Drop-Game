#pragma once
#include <vector>
#include <map>
#include "GameState.h"

class GameStateManager
{
	std::map<GAME_STATE_ENUM, GameState*> gameStates;
	
	GameState* currentGameState;
	GameState* newGameState;
	
	bool changedState;
	bool isPaused;
public:
	/// <summary>
	/// Manages the switching and changing between the states.
	/// </summary>
	GameStateManager();
	~GameStateManager();

	/// <summary>
	/// Initialise states.
	/// </summary>
	void Init();

	/// <summary>
	/// Check if state should be changed. Needs to be called every frame.
	/// </summary>
	void Update();

	/// <summary>
	/// Change the game state.
	/// </summary>
	/// <param name="gameStateToChangeTo">Which game state to change to.</param>
	void ChangeState(GAME_STATE_ENUM gameStateToChangeTo);

	/// <summary>
	/// Get the current states enum value.
	/// </summary>
	/// <returns>Current state.</returns>
	inline GAME_STATE_ENUM GetCurrentState() const { return currentGameState->GetStateAssociatedWith(); }

	/// <summary>
	/// Is the game paused.
	/// </summary>
	/// <returns>Is the game paused.</returns>
	bool IsPaused();
};

