#include "InstructionsState.h"

#include "Game.h"
#include "GameObjectManager.h"

#include "Sprite2DComponent.h"
#include "StateChangeButton2DComponent.h"
#include "Text2DComponent.h"

InstructionsState::InstructionsState()
	: GameState(GAME_STATE_ENUM::INSTRCUTIONS)
{
}


InstructionsState::~InstructionsState()
{
}

void InstructionsState::LoadIn()
{
	//add instructions image and header text
	{
		auto contentsObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		std::string titleText = "Instructions";
		float titleTextLength = Game::GetAssetManager()->GetFont("comic sans")->GetStringLength(titleText.data());
		contentsObj->AddComponent(new Text2DComponent(Game::GetAssetManager()->GetFont("comic sans"), titleText,
			{960.f / 2.f - (titleTextLength / 2.f), 544.f * (1.f / 10.f), 0.f}, 1.f,
			gef::Colour(1.f, 1.f, 1.f)));

		auto insructionsSprite = new gef::Sprite();
		insructionsSprite->set_texture(Game::GetAssetManager()->GetTexture("controls"));
		insructionsSprite->set_position({ 960.f / 2.f, 544.f / 2.f, 0.f });
		insructionsSprite->set_width(768.f);
		insructionsSprite->set_height(341.3f);

		contentsObj->AddComponent(new Sprite2DComponent(insructionsSprite));
	}

	//add main menu button
	{
		auto mainMenuButtonObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		auto mainMenuSprite = new gef::Sprite();
		mainMenuSprite->set_width(64.f);
		mainMenuSprite->set_height(64.f);
		mainMenuSprite->set_position(10.f + mainMenuSprite->width(), 544.f - 10.f - mainMenuSprite->height(), 0.f);
		mainMenuSprite->set_texture(Game::GetAssetManager()->GetTexture("exit button"));

		mainMenuButtonObj->AddComponent(new Sprite2DComponent(mainMenuSprite));

		mainMenuButtonObj->AddComponent(new StateChangeButton2DComponent({ {mainMenuSprite->position().x() - (mainMenuSprite->width() / 2.f), mainMenuSprite->position().y() - (mainMenuSprite->height() / 2.f)},
			{mainMenuSprite->width(), mainMenuSprite->height()} },
			GAME_STATE_ENUM::MAIN_MENU,
			true));
	}
}
