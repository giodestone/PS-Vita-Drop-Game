#pragma once
#include "Component.h"
#include "Rect.h"
#include "Sprite2DComponent.h"

class ChangeDifficultyButton2DComponent :
	public Component
{
	Rect location;
	float newDifficulty;
	bool isEnabled;

	int currentTouch;
	Sprite2DComponent* sprite;
public:
	/// <summary>
	/// Component which is a button for changing the difficulty of the game. Works by modifying Game::Configuration().DifficultyMultiplyer
	/// </summary>
	/// <param name="location">Where it is.</param>
	/// <param name="newDifficulty">What the new difficulty should be when its clicked, and also when it will be green.</param>
	/// <param name="sprite">Sprite component so it can update the colour.</param>
	/// <param name="isEnabled">Is it enabled.</param>
	ChangeDifficultyButton2DComponent(Rect location, float newDifficulty, Sprite2DComponent* sprite, bool isEnabled);
	~ChangeDifficultyButton2DComponent();

	/// <summary>
	/// Check for touches. If touched update difficulty and change colour.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller);

private:
	/// <summary>
	/// Change the difficulty of the game.
	/// </summary>
	void updateDifficulty();

	/// <summary>
	/// Update the colour of the sprite depending on what the difficulty level is. It will glow green if it is the same as the difficulty the button is associated with.
	/// </summary>
	void updateColor();
};

