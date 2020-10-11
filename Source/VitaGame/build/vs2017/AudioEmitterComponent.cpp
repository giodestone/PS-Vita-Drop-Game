#include "AudioEmitterComponent.h"

#include "GameObject.h"

AudioEmitterComponent::AudioEmitterComponent(AudioEmitter * audioEmitter)
	: Component(COMPONENT_TAG::AUDIO_EMITTER),
	audioEmitter(audioEmitter)
{
	if (!audioEmitter->added_to_audio3d()) //this prevents an easy mistake
		Game::GetAudio3D()->AddEmitter(audioEmitter);

	audioEmitter->ownerComponent = this;
}

AudioEmitterComponent::~AudioEmitterComponent()
{
	if (audioEmitter != nullptr)
		audioEmitter->set_to_be_deleted(true); //just mark the audio emitter to be deleted by audio 3d
}

void AudioEmitterComponent::Update(float dt, GameObject * caller)
{
	// THERE WILL PROBABLY BE PROBLEMS WITH THIS LATER ON AS if the audio emitter stops playing sounds it will be deleted, in turn it might be best to just delete this component if that happens.
	updatePositionFromGameObject(caller);
}

void AudioEmitterComponent::updatePositionFromGameObject(GameObject* obj)
{
	if (audioEmitter != nullptr)
		audioEmitter->set_position(obj->GetTransform().Position());
	else
		this->Delete();
}
