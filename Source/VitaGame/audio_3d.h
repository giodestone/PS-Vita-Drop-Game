#ifndef _AUDIO_3D_H
#define _AUDIO_3D_H

#include <audio/audio_manager.h>
#include "audio_listener.h"
#include "audio_emitter.h"
#include <vector>


/// <summary>
/// For making the audio stereo and also chaning the sound.
/// </summary>
class Audio3D
{
public:
	Audio3D(gef::AudioManager* audio_manager);
	~Audio3D();

	void Update();

	void AddEmitter(AudioEmitter* emitter);

	inline AudioListener& Listener() { return listener_; }

private:
	gef::AudioManager* audio_manager_;
	AudioListener listener_;

	std::vector<AudioEmitter*> emitters_;
//	AudioEmitter emitters_[20];
};

#endif // _AUDIO_3D_H