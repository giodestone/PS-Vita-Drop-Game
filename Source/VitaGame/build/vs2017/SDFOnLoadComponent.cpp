#include "SDFOnLoadComponent.h"

#include "GameObject.h"

SDFOnLoadComponent::SDFOnLoadComponent(std::atomic<bool>* isLoading)
	: Component(COMPONENT_TAG::UNDEFINED_COMPONENT_TAG),
	isLoading(isLoading)
{}

SDFOnLoadComponent::~SDFOnLoadComponent()
{}

void SDFOnLoadComponent::Update(float dt, GameObject * caller)
{
	if  (isLoading->load() == false)
	{
		Game::GetGameStateManager()->ChangeState(GAME_STATE_ENUM::MAIN_MENU);
	}
}
