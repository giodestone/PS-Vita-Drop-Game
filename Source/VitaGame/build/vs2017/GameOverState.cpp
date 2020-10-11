#include "GameOverState.h"

#include <sstream>

#include "Game.h"
#include "GameObjectManager.h"

#include "Text2DComponent.h"
#include "Sprite2DComponent.h"
#include "StateChangeButton2DComponent.h"

GameOverState::GameOverState()
	: GameState(GAME_STATE_ENUM::GAME_OVER)
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::LoadIn()
{
	auto rootObject = Game::GetGameObjectManager()->AddObject(new GameObject());
	//game over title
	{
		std::string titleText = "Game Over!";
		float titleTextLength = Game::GetAssetManager()->GetFont("comic sans")->GetStringLength(titleText.data());
		rootObject->AddComponent(new Text2DComponent(Game::GetAssetManager()->GetFont("comic sans"), titleText,
			{ 960.f / 2.f - ((titleTextLength * 1.1f) / 2.f), 544.f * (2.f / 10.f), 1.f }, 1.1f,
			gef::Colour(1.f, 1.f, 1.f)));
	}

	//game score
	{
		std::stringstream ss;
		ss << "Your Score: ";
		ss << Game::GetScore();
		std::string scoreText = ss.str();
		float scoreTextLength = Game::GetAssetManager()->GetFont("comic sans")->GetStringLength(scoreText.data());
		rootObject->AddComponent(new Text2DComponent(Game::GetAssetManager()->GetFont("comic sans"), scoreText,
			{ 960.f / 2.f - ((scoreTextLength * 1.25f) / 2.f), 544.f * (5.f / 10.f), 1.f }, 1.25f,
			gef::Colour(1.f, 1.f, 1.f)));
	}

	//go to main menu button
	{
		auto mainMenuSprite = new gef::Sprite();
		mainMenuSprite->set_width(64.f);
		mainMenuSprite->set_height(64.f);
		mainMenuSprite->set_position(10.f + mainMenuSprite->width(), 544.f - 10.f - mainMenuSprite->height(), 0.f);
		mainMenuSprite->set_texture(Game::GetAssetManager()->GetTexture("exit button"));

		rootObject->AddComponent(new Sprite2DComponent(mainMenuSprite));

		rootObject->AddComponent(new StateChangeButton2DComponent({ {mainMenuSprite->position().x() - (mainMenuSprite->width() / 2.f), mainMenuSprite->position().y() - (mainMenuSprite->height() / 2.f)},
			{mainMenuSprite->width(), mainMenuSprite->height()} },
			GAME_STATE_ENUM::MAIN_MENU,
			true));
	}

	//retry button
	{
		auto retrySprite = new gef::Sprite();
		retrySprite->set_width(64.f);
		retrySprite->set_height(64.f);
		retrySprite->set_position(960.f / 2.f, 544.f - 10.f - retrySprite->height(), 0.f);
		retrySprite->set_texture(Game::GetAssetManager()->GetTexture("replay button"));

		rootObject->AddComponent(new Sprite2DComponent(retrySprite));

		rootObject->AddComponent(new StateChangeButton2DComponent({ {retrySprite->position().x() - (retrySprite->width() / 2.f), retrySprite->position().y() - (retrySprite->height() / 2.f)},
			{retrySprite->width(), retrySprite->height()} },
			GAME_STATE_ENUM::IN_GAME,
			true));
	}
}

void GameOverState::CleanUp()
{
	Game::SetScore(0); //reset score.
}
