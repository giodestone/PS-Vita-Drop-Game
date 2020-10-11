#include "OptionsState.h"

#include "Game.h"
#include "GameObjectManager.h"

#include "Text2DComponent.h"
#include "Sprite2DComponent.h"
#include "StateChangeButton2DComponent.h"
#include "TickButton2DComponent.h"
#include "ChangeDifficultyButton2DComponent.h"

OptionsState::OptionsState()
	: GameState(GAME_STATE_ENUM::OPTIONS)
{
}


OptionsState::~OptionsState()
{
}

void OptionsState::LoadIn()
{
	//put score title in
	{
		auto scoreTileState = Game::GetGameObjectManager()->AddObject(new GameObject());
		auto highScoreText = "Settings";
		scoreTileState->AddComponent(new Text2DComponent(
			Game::GetAssetManager()->GetFont("comic sans"), 
			highScoreText, 
			{ (960.f / 2.f), 544.f * (1.f / 10.f), 0.f }, 
			1.f, 
			gef::Colour(1.f, 1.f, 1.f), 
			gef::TextJustification::TJ_CENTRE));
	}

	//Toggle music
	{
		auto tickedButtonObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		auto tickedButtonSprite = new gef::Sprite();
		tickedButtonSprite->set_position(960.f * (1.f / 6.f), 544.f * (2.f / 10.f), 0.f);
		tickedButtonSprite->set_width(64.f);
		tickedButtonSprite->set_height(64.f);
		tickedButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("unticked"));
		auto tickedButtonSpriteComp = tickedButtonObj->AddComponent(new Sprite2DComponent(tickedButtonSprite));
		tickedButtonObj->AddComponent(new TickButton2DComponent(
			{ { tickedButtonSprite->position().x() - (tickedButtonSprite->width() / 2.f), tickedButtonSprite->position().y() - (tickedButtonSprite->height() / 2.f) },
			{ tickedButtonSprite->width(), tickedButtonSprite->height() } },
			true,
			&Game::Configuration().PlayMusic,
			static_cast<Sprite2DComponent*>(tickedButtonSpriteComp)));

		tickedButtonObj->AddComponent(new Text2DComponent(Game::GetAssetManager()->GetFont("comic sans"), "Music",
			{ tickedButtonSprite->position().x() + tickedButtonSprite->width() + 20.f, tickedButtonSprite->position().y() - 6.5f, 0.f },
			1.f,
			gef::Colour(1.f, 1.f, 1.f)
		));
	}

	//Add Difficulty options (tickbox with text underneath)

	//easy
	{
		auto easyButtonObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		
		auto easyButtonSprite = new gef::Sprite();
		easyButtonSprite->set_position(960.f * (3.f / 7.f) - (128.f / 2.f), 544.f * (5.f / 10.f), 0.f);
		easyButtonSprite->set_width(128.f);
		easyButtonSprite->set_height(64.f);
		easyButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("easy button"));
		auto easyButtonSpriteComp = easyButtonObj->AddComponent(new Sprite2DComponent(easyButtonSprite));

		easyButtonObj->AddComponent(new ChangeDifficultyButton2DComponent(
			{ { easyButtonSprite->position().x() - (easyButtonSprite->width() / 2.f), easyButtonSprite->position().y() - (easyButtonSprite->height() / 2.f) },
			{ easyButtonSprite->width(), easyButtonSprite->height() } },
			0.6f,
			static_cast<Sprite2DComponent*>(easyButtonSpriteComp),
			true));
	}
	//med
	{
		auto medButtonObj = Game::GetGameObjectManager()->AddObject(new GameObject());
		
		auto medButtonSprite = new gef::Sprite();
		medButtonSprite->set_position(960.f * (4.f / 7.f) - (128.f / 2.f), 544.f * (5.f / 10.f), 0.f);
		medButtonSprite->set_width(128.f);
		medButtonSprite->set_height(64.f);
		medButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("medium button"));
		auto medButtonSpriteComp = medButtonObj->AddComponent(new Sprite2DComponent(medButtonSprite));

		medButtonObj->AddComponent(new ChangeDifficultyButton2DComponent(
			{ { medButtonSprite->position().x() - (medButtonSprite->width() / 2.f), medButtonSprite->position().y() - (medButtonSprite->height() / 2.f) },
			{ medButtonSprite->width(), medButtonSprite->height() } },
			0.8f,
			static_cast<Sprite2DComponent*>(medButtonSpriteComp),
			true));
	}
	//hard
	{
		auto hardButtonObj = Game::GetGameObjectManager()->AddObject(new GameObject());

		auto hardButtonSprite = new gef::Sprite();
		hardButtonSprite->set_position(960.f * (5.f / 7.f) - (128.f / 2.f), 544.f * (5.f / 10.f), 0.f);
		hardButtonSprite->set_width(128.f);
		hardButtonSprite->set_height(64.f);
		hardButtonSprite->set_texture(Game::GetAssetManager()->GetTexture("hard button"));
		auto hardSpriteComp = hardButtonObj->AddComponent(new Sprite2DComponent(hardButtonSprite));

		hardButtonObj->AddComponent(new ChangeDifficultyButton2DComponent(
			{ { hardButtonSprite->position().x() - (hardButtonSprite->width() / 2.f), hardButtonSprite->position().y() - (hardButtonSprite->height() / 2.f) },
			{ hardButtonSprite->width(), hardButtonSprite->height() } },
			1.f,
			static_cast<Sprite2DComponent*>(hardSpriteComp),
			true));
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
