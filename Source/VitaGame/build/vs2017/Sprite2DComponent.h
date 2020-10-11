#pragma once
#include "Component.h"
#include <graphics/sprite.h>
class Sprite2DComponent :
	public Component
{
	gef::Sprite* sprite;

	bool shouldRender;

public:
	/// <summary>
	/// This component is for adding a sprite to a game object. 
	/// Note it will not track the game objects position, but rather its own.
	/// </summary>
	/// <param name="sprite"></param>
	/// <param name="shouldRender">Whether or not the sprite should be getting rendered.</para>
	Sprite2DComponent(gef::Sprite* sprite, bool shouldRender = true);
	~Sprite2DComponent();

	/// <summary>
	/// Renders the sprite to screen
	/// </summary>
	/// <param name="caller"></param>
	void Render2D(class GameObject* caller) override;

	/// <summary>
	/// Get the underlying spirte.
	/// </summary>
	/// <returns>Sprite.</returns>
	inline gef::Sprite* GetSprite() { return sprite; }

	/// <summary>
	/// Should the sprite be rendered to screen.
	/// </summary>
	/// <returns>Whether or not the sprite should be rendered to screen.</returns>
	inline bool ShouldRender() { return shouldRender; }
	
	/// <summary>
	/// Set whether the sprite should be rendered.
	/// </summary>
	/// <param name="shouldRender">If the sprite should be rendered or not.</param>
	inline void SetShouldRender(bool shouldRender) { this->shouldRender = shouldRender; }
};

