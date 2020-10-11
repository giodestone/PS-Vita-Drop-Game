#include "BoundaryComponent.h"

#include "GameObject.h"

BoundaryComponent::BoundaryComponent()
	: Component(COMPONENT_TAG::BOUNDARY)
{}


BoundaryComponent::~BoundaryComponent()
{}

void BoundaryComponent::CollisionResponse(GameObject * other)
{
	if (other != nullptr) //redundant check
	{
		switch (other->GetTag())
		{
		case TAG::PLAYER_BALL: //if touching the ball.
			Game::GetGameStateManager()->ChangeState(GAME_STATE_ENUM::GAME_OVER);
			break;
		case TAG::SPAWNED_OBJECT: //if touching something spawned.
			other->Remove();
			break;
		}
	}
}
