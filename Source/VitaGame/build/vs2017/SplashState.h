#pragma once
#include <atomic>
#include <thread>

#include "GameState.h"

#include "GameObject.h"

class SplashState :
	public GameState
{
	GameObject* splash;

	std::atomic<bool> isLoading;
	std::thread loadingThread;
public:
	/// <summary>
	/// Responisble for displaying a splash screen and loading anything (in a seperate thread).
	/// </summary>
	SplashState();
	~SplashState();

	void LoadIn() override;
	void CleanUp() override;

	/// <summary>
	/// Function for loading anything that itsnt needed by the sprite.
	/// </summary>
	/// <param name="isLoading"></param>
	static void LoadStuffThreadFunc(std::atomic<bool>* isLoading);
};

