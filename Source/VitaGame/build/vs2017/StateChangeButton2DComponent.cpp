#include "StateChangeButton2DComponent.h"

#include "Game.h"
#include <input/input_manager.h>
#include <input/touch_input_manager.h>

StateChangeButton2DComponent::StateChangeButton2DComponent(Rect location, GAME_STATE_ENUM gameStateToSwitchTo, bool isEnabled)
	: Component (COMPONENT_TAG::CHANGE_STATE_ON_PRESS),
	location(location),
	gameStateToSwitchTo(gameStateToSwitchTo),
	isEnabled(isEnabled),
	currentTouch(-1)
{
}

StateChangeButton2DComponent::~StateChangeButton2DComponent()
{
}

void StateChangeButton2DComponent::Update(float dt, GameObject * caller)
{
	//check if any buttons have been clicked

	const gef::TouchInputManager* touchInput = Game::GetInputManager()->touch_manager();
	if (touchInput->max_num_panels() > 0)
	{
		const gef::TouchContainer& panelTouches = touchInput->touches(0); //get touches
																			// go through the touches
		for (gef::ConstTouchIterator touch = panelTouches.begin(); touch != panelTouches.end(); ++touch)
		{
			// if active touch id is -1, then we are not currently processing a touch
			if (currentTouch == -1)
			{
				// check for the start of a new touch
				if (touch->type == gef::TT_NEW)
				{
					currentTouch = (*touch).id;
					if ((*touch).position.x >= location.Pos.x && (*touch).position.x < location.Pos.x + location.Dimensions.x &&
						(*touch).position.y >= location.Pos.y && (*touch).position.y < location.Pos.y + location.Dimensions.y)
					{
						if (isEnabled)
							changeState();

					}
				}
			}
			else if (currentTouch == touch->id)
			{
				// we are processing touch data with a matching id to the one we are looking for
				if (touch->type == gef::TT_ACTIVE)
				{
					// update an active touch here
					// we're just going to record the position of the touch
					/*Game::CurrentTouchID = (*touch).position;*/
				}
				else if (touch->type == gef::TT_RELEASED)
				{
					// the touch we are tracking has been released
					// perform any actions that need to happen when a touch is released here
					// we're not doing anything here apart from resetting the active touch id
					currentTouch = -1;
				}
			}
		}
	}
}

void StateChangeButton2DComponent::changeState() 
{ 
	Game::GetGameStateManager()->ChangeState(gameStateToSwitchTo); 
}
