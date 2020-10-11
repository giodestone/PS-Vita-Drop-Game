#pragma once
#include "Component.h"

#include "GameStateEnum.h"

#include <maths/vector2.h>
#include <atomic>

#include "Rect.h"

class StateChangeButton2DComponent :
	public Component
{
	GAME_STATE_ENUM gameStateToSwitchTo;
	Rect location;
	bool isEnabled;

	int currentTouch;
public:
	/// <summary>
	/// Changes state when pressed.
	/// </summary>
	/// <param name="location">The location of the button in terms of x, y, w, h. Remember sprites have their origin in the middle.</param>
	/// <param name="gameStateToSwitchTo">Which gamestate will the button switch to when pressed.</param>
	/// <param name="isEnabled">Should the button be clickable.</param>
	StateChangeButton2DComponent(Rect location, GAME_STATE_ENUM gameStateToSwitchTo, bool isEnabled);
	~StateChangeButton2DComponent();

	void Update(float dt, class GameObject* caller) override;

	/// <summary>
	/// Is the button enabled.
	/// </summary>
	/// <returns>Whether is the button enabled.</returns>
	inline bool& IsEnabled() { return isEnabled; }
	/// <summary>
	/// Make the button enabled or disabled.
	/// </summary>
	/// <param name="isEnabled">Whether the button should be enabled or disabled.</param>
	inline void SetEnabled(bool isEnabled) { this->isEnabled = isEnabled; }

private:
	/// <summary>
	/// Change the state
	/// </summary>
	void changeState();
};

