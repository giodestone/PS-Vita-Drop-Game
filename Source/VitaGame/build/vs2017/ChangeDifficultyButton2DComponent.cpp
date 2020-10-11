#include "ChangeDifficultyButton2DComponent.h"

#include "Game.h"
#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <graphics/colour.h>

ChangeDifficultyButton2DComponent::ChangeDifficultyButton2DComponent(Rect location, float newDifficulty, Sprite2DComponent* sprite, bool isEnabled)
	: Component(COMPONENT_TAG::CHANGE_DIFFICULTY_BUTTON),
	location(location),
	newDifficulty(newDifficulty),
	sprite(sprite),
	isEnabled(isEnabled),
	currentTouch(-1)
{
	updateColor();
}

ChangeDifficultyButton2DComponent::~ChangeDifficultyButton2DComponent()
{
}

void ChangeDifficultyButton2DComponent::Update(float dt, GameObject * caller)
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
							updateDifficulty();
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
					updateColor();
					currentTouch = -1;
				}
			}
		}
	}
}

void ChangeDifficultyButton2DComponent::updateDifficulty()
{
	Game::Configuration().DifficultyMultiplyer = newDifficulty;
}

void ChangeDifficultyButton2DComponent::updateColor()
{
	if (std::fabs(Game::Configuration().DifficultyMultiplyer - newDifficulty) < 0.01f) //if equal to -- this is just for safety
	{
		sprite->GetSprite()->set_colour(gef::Colour(0.6f, 1.f, 0.6f).GetABGR());
	}
	else
	{
		sprite->GetSprite()->set_colour(gef::Colour(1.f, 1.f, 1.f).GetABGR());
	}
}
