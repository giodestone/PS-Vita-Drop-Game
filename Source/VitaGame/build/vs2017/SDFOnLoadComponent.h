#pragma once
#include "Component.h"

#include <atomic>

class SDFOnLoadComponent :
	public Component
{
	std::atomic<bool>* isLoading;

public:
	/// <summary>
	/// Component for changing states when the game is loaded. 
	/// </summary>
	/// <param name="isLoading">Atomic which holds if the game is loading.</param>
	SDFOnLoadComponent(std::atomic<bool>* isLoading);
	~SDFOnLoadComponent();

	/// <summary>
	/// Check if the game has loaded, and if so switch to main menu.
	/// </summary>
	/// <param name="dt">Not used.</param>
	/// <param name="caller">Not used.</param>
	void Update(float dt, class GameObject* caller) override;
};

