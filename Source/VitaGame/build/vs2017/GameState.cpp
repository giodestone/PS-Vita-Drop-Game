#include "GameState.h"

GameState::GameState(GAME_STATE_ENUM gameStateAssociatedWith)
	: gameStateAssociatedWith(gameStateAssociatedWith)
{}

GameState::~GameState()
{}

void GameState::LoadIn()
{}

void GameState::CleanUp()
{}
