#pragma once
#include "Component.h"

#include "audio_listener.h"

class AudioListenerComponent :
	public Component
{
	static bool doesListenerComponentExist; //For keeping track if more than one exists.
public:
	/// <summary>
	/// A component for basically wrapping around the audio 3d listener and updating its poisiton.
	/// </summary>
	AudioListenerComponent();
	~AudioListenerComponent();

	/// <summary>
	/// Updates the audio listener position from the game object.
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="caller"></param>
	void Update(float dt, GameObject* caller) override;

private:
	/// <summary>
	/// Update the audio listener positon from the game object.
	/// </summary>
	/// <param name="obj">Object to get the position from.</param>
	void updateAudioListenerPositon(GameObject* obj);
};

