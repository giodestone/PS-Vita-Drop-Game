#pragma once
#include "Component.h"

#include "Sprite2DComponent.h"
#include "Rect.h"

class TickButton2DComponent :
	public Component
{
	bool* optionToTrack;
	Rect location;
	bool isEnabled;
	Sprite2DComponent* sprite2DComponent;

	int currentTouch;

public:
	/// <summary>
	/// Component for a tick box button.
	/// </summary>
	/// <param name="pos">Position on screen.</param>
	/// <param name="isEnabled"></param>
	/// <param name="optionToTrack">The boolean that this will change.</param>
	/// <param name="sprite2DComponent">Sprite that should be updated with a ticked or unticked texture.</param>
	TickButton2DComponent(Rect pos, bool isEnabled, bool* optionToTrack, Sprite2DComponent* sprite2DComponent);
	~TickButton2DComponent();

	/// <summary>
	/// Check if the button is being clicked, and if so change the sprite, invert the option that its tracking.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
private:
	/// <summary>
	/// Change the sprites texture between ticked and unticked.
	/// </summary>
	void updateSprite();
};

