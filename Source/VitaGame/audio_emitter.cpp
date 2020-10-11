#include "audio_emitter.h"

#include "AudioEmitterComponent.h"

AudioEmitter::AudioEmitter() :
	position_(gef::Vector4::kZero),
	sfx_id_(-1),
	playing_(false),
	voice_id_(-1),
	radius_(1.0f),
	looping_(false),
	added_to_audio3d_(false),
	is_to_be_deleted(false)
{
}

AudioEmitter::~AudioEmitter()
{
	if (ownerComponent != nullptr)
	{
		ownerComponent->Delete();
		ownerComponent->audioEmitter = nullptr;
	}
}

void AudioEmitter::Init(int sfx_id, bool looping, AudioEmitterComponent* ownerComponent)
{
	sfx_id_ = sfx_id;
	looping_ = looping;
	this->ownerComponent = ownerComponent;
}

void AudioEmitter::SoundStarted(int voice_num)
{
	voice_id_ = voice_num;
	playing_ = true;
}

void AudioEmitter::SoundStopped()
{
	playing_ = false;
	voice_id_ = -1;
}
