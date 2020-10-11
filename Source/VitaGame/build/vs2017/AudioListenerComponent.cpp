#include "AudioListenerComponent.h"

#include <system/debug_log.h>

#include "GameObject.h"

bool AudioListenerComponent::doesListenerComponentExist = false;

AudioListenerComponent::AudioListenerComponent()
	: Component(COMPONENT_TAG::AUDIO_LISTENER)
{
	if (doesListenerComponentExist)
		gef::DebugOut("GAME ERROR: An AudioListnenerComponent already exists! (See when objects are getting added or others from the old scene have been deleted).");
	else
		doesListenerComponentExist = true;
}

AudioListenerComponent::~AudioListenerComponent()
{
	doesListenerComponentExist = false;
}

void AudioListenerComponent::Update(float dt, GameObject * caller)
{
	updateAudioListenerPositon(caller);
}

void AudioListenerComponent::updateAudioListenerPositon(GameObject* obj)
{
	Game::GetAudio3D()->Listener().SetTransform(obj->GetTransform().GetMatrix());
}
