#pragma once
#include "Component.h"

#include "Sprite2DComponent.h"

class FloatSprite2DComponent :
	public Component
{
	Sprite2DComponent* spriteToFloat;

	float amplidtude, frequency, timeElapsed;
public:
	/// <summary>
	/// This component makes a sprite appear like its floating up and down (y axis).
	/// </summary>
	/// <param name="spriteToFloat"></param>
	/// <param name="amplitude">How far up and down it will go.</param>
	/// <param name="frequency">How quickly it will do it.</param>
	FloatSprite2DComponent(Sprite2DComponent* spriteToFloat, float amplitude, float frequency);
	~FloatSprite2DComponent();

	/// <summary>
	/// Update the position of the sprite along the sine wave.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
};

