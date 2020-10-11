#include "TickButton2DComponent.h"

#include "Game.h"
#include <input/input_manager.h>
#include <input/touch_input_manager.h>

TickButton2DComponent::TickButton2DComponent(Rect pos, bool isEnabled, bool * optionToTrack, Sprite2DComponent* sprite2DComponent)
	: Component(COMPONENT_TAG::TICK_BUTTON),
	location(pos),
	isEnabled(isEnabled),
	optionToTrack(optionToTrack),
	sprite2DComponent(sprite2DComponent),
	currentTouch(-1)
{
	updateSprite();
}

TickButton2DComponent::~TickButton2DComponent()
{
}

void TickButton2DComponent::Update(float dt, GameObject * caller)
{
	
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
						{
							(*optionToTrack) = !(*optionToTrack); //change option
							
							updateSprite();
						}
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

void TickButton2DComponent::updateSprite()
{
	if ((*optionToTrack)) //update sprite
	{
		sprite2DComponent->GetSprite()->set_texture(Game::GetAssetManager()->GetTexture("ticked"));
	}
	else
	{
		sprite2DComponent->GetSprite()->set_texture(Game::GetAssetManager()->GetTexture("unticked"));
	}
}
