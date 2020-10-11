#include "GamePauserComponent.h"

#include "Game.h"
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include "GameObjectManager.h"

GamePauserComponent::GamePauserComponent(Text2DComponent* pauseText, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> mainMenu, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> pause, std::pair<Sprite2DComponent*, StateChangeButton2DComponent*> unpause)
	: Component(COMPONENT_TAG::GAME_PAUSER),
	wasPausedDown(false),

	pauseText(pauseText),
	mainMenu(mainMenu),
	pause(pause),
	unpause(unpause)
{
}


GamePauserComponent::~GamePauserComponent()
{
}

void GamePauserComponent::Update(float dt, GameObject * caller)
{
	updatePauseStartBtnShortcut();

	updateVisibleAndActive();
}

void GamePauserComponent::updateVisibleAndActive()
{
	pauseText->SetShouldRender(Game::GetGameStateManager()->IsPaused());

	unpause.first->SetShouldRender(Game::GetGameStateManager()->IsPaused());
	unpause.second->SetEnabled(Game::GetGameStateManager()->IsPaused());

	mainMenu.first->SetShouldRender(Game::GetGameStateManager()->IsPaused());
	mainMenu.second->SetEnabled(Game::GetGameStateManager()->IsPaused());

	pause.first->SetShouldRender(!Game::GetGameStateManager()->IsPaused());
	pause.second->SetEnabled(!Game::GetGameStateManager()->IsPaused());
}

void GamePauserComponent::updatePauseStartBtnShortcut()
{
	const gef::SonyController* controller = Game::GetInputManager()->controller_input()->GetController(0);

	if ((controller->buttons_down() & gef_SONY_CTRL_START) && !wasPausedDown)
	{
		wasPausedDown = true;
		pauseUnpause();
	}
	else if (!(controller->buttons_down() & gef_SONY_CTRL_START))
	{
		wasPausedDown = false;
	}
}

void GamePauserComponent::pauseUnpause()
{
	if (Game::GetGameStateManager()->IsPaused())
		Game::GetGameStateManager()->ChangeState(GAME_STATE_ENUM::IN_GAME);
	else
		Game::GetGameStateManager()->ChangeState(GAME_STATE_ENUM::PAUSE);
}
