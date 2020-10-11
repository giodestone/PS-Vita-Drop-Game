#pragma once
#include "Component.h"
class MusicPlayingComponent :
	public Component
{
	bool stopOnDestory;

public:
	/// <summary>
	/// Component which plays music and checks if it should be playing or not.
	/// </summary>
	/// <param name="stopOnDestroy">Whether the music should stop when the component is destroyed.</param>
	MusicPlayingComponent(bool stopOnDestory);
	~MusicPlayingComponent();

	/// <summary>
	/// Checks if the music should be playing.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
};

