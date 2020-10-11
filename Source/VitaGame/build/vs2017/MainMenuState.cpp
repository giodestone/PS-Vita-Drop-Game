#include "MainMenuState.h"

#include <graphics/texture.h>

#include "Game.h"
#include "GameObjectManager.h"

#include "StateChangeButton2DComponent.h"
#include "Sprite2DComponent.h"


MainMenuState::MainMenuState()
	: GameState(GAME_STATE_ENUM::MAIN_MENU)
{}


MainMenuState::~MainMenuState()
{}

void MainMenuState::LoadIn()
{
	/*logo across top, square buttons across bottom next to each other*/
	/*Buttons 3,4,5,6,7 /10 -- play, instructions, settings, high scores, exit*/

	//add logo
	{
		auto logoObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		gef::Sprite* sp = new gef::Sprite();
		sp->set_texture(Game::GetAssetManager()->GetTexture("logo"));
		sp->set_width(256.f);
		sp->set_height(128.f);
		sp->set_position({ (960.f / 2.f), (544.f * (1.f / 4.f)), 0.f }); //put it at centre of the screen.
		logoObj->AddComponent(new Sprite2DComponent(sp));
	}

	//Add buttons
	addButton(3.f, Game::GetAssetManager()->GetTexture("play button"), GAME_STATE_ENUM::IN_GAME);
	addButton(4.f, Game::GetAssetManager()->GetTexture("instructions button"), GAME_STATE_ENUM::INSTRCUTIONS);
	//addButton(5.f, Game::GetAssetManager()->GetTexture("high score button"), GAME_STATE_ENUM::INVALID_STATE);
	addButton(5.f, Game::GetAssetManager()->GetTexture("settings button"), GAME_STATE_ENUM::OPTIONS);
	addButton(6.f, Game::GetAssetManager()->GetTexture("exit button"), GAME_STATE_ENUM::EXIT);
}

void MainMenuState::CleanUp()
{
	
}

void MainMenuState::addButton(float pos, gef::Texture * texture, GAME_STATE_ENUM stateToChangeTo)
{
	const float buttonY = 544.f * (4.f / 6.f);
	const float buttonSize = 64.f; //NEEDS TO MATCH SIZE OF SPRITES

	auto buttonObj = Game::GetGameObjectManager()->AddObject(new GameObject());
	auto buttonSprite = new gef::Sprite();
	buttonSprite->set_position(960.f * (pos / 9.f), buttonY, 0.f);
	buttonSprite->set_texture(texture);
	buttonSprite->set_width(buttonSize);
	buttonSprite->set_height(buttonSize);
	auto buttonSpriteComp = buttonObj->AddComponent(new Sprite2DComponent(buttonSprite));

	buttonObj->AddComponent(new StateChangeButton2DComponent(
		{ { buttonSprite->position().x() - (buttonSprite->width() / 2.f), buttonSprite->position().y() - (buttonSprite->height() / 2.f) },
		{ buttonSprite->width(), buttonSprite->height() } },
		stateToChangeTo,
		true));
}
