#include "GameStateManager.h"

#include "Game.h"
#include "GameObjectManager.h"

#include "SplashState.h"
#include "MainMenuState.h"
#include "InGameState.h"
#include "OptionsState.h"
#include "InstructionsState.h"
#include "GameOverState.h"

GameStateManager::GameStateManager()
	: changedState(false),
	isPaused(false)
{
}


GameStateManager::~GameStateManager()
{
	for (auto it = gameStates.begin(); it != gameStates.end();)
	{
		delete (*it).second;
		(*it).second = nullptr;
		it = gameStates.erase(it);
	}
}

void GameStateManager::Init()
{
	//Add all game states.
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::SPLASH, new SplashState()));
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::MAIN_MENU, new MainMenuState()));
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::IN_GAME, new InGameState()));
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::OPTIONS, new OptionsState()));
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::INSTRCUTIONS, new InstructionsState()));
	gameStates.insert(std::pair<GAME_STATE_ENUM, GameState*>(GAME_STATE_ENUM::GAME_OVER, new GameOverState()));

	//now switch to the spalsh
	currentGameState = gameStates.at(GAME_STATE_ENUM::SPLASH);
	currentGameState->LoadIn();
	newGameState = currentGameState;
}

void GameStateManager::Update()
{
	if (changedState)
	{
		newGameState->LoadIn();
		currentGameState = newGameState;
		changedState = false;
	}

	if (currentGameState != newGameState)
	{
		currentGameState->CleanUp();
		Game::GetGameObjectManager()->RemoveAll();
		changedState = true; //as we have to delay the operation by an update cycle (see GameObjectManager::RemoveAll() remarks).
	}
}

void GameStateManager::ChangeState(GAME_STATE_ENUM gameStateToChangeTo)
{
	if (gameStateToChangeTo == GAME_STATE_ENUM::EXIT) //if exit
	{
		Game::Exit();
		return;
	}

	if (gameStateToChangeTo == GAME_STATE_ENUM::PAUSE) //if should pause
	{
		isPaused = true;
		return;
	}
	
	if (gameStateToChangeTo == GAME_STATE_ENUM::IN_GAME && isPaused) //if should unpause
	{
		isPaused = false;
		return;
	}
	
	isPaused = false;
	newGameState = gameStates.at(gameStateToChangeTo); //otherwise change state
}

bool GameStateManager::IsPaused() 
{ 
	return isPaused; 
}
