#pragma once
#include "Component.h"

#include "audio_emitter.h"

class AudioEmitterComponent :
	public Component
{
	friend AudioEmitter;
	AudioEmitter* audioEmitter;
public:
	/// <summary>
	/// A wrapper aroudn the AudioEmitter class to work with components.
	/// </summary>
	/// <param name="audioEmitter">Pointer to an emmitter. Gets added to Audio3D if it hasn't been already.</param>
	AudioEmitterComponent(AudioEmitter* audioEmitter);
	~AudioEmitterComponent();

	/// <summary>
	/// Updates the position of the emitter from the game object.
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="caller"></param>
	void Update(float dt, class GameObject* caller) override;

	/// <summary>
	/// Gets the audio emitter.
	/// </summary>
	/// <returns>Audio Emitter.</returns>
	AudioEmitter& GetAudioEmitter() { return *audioEmitter; }
private:
	/// <summary>
	/// Updates the game position from the game object.
	/// </summary>
	/// <param name="obj">The game object to get the positon from.</param>
	void updatePositionFromGameObject(class GameObject* obj);
};

