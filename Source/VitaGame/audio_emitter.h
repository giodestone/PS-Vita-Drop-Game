#ifndef _AUDIO_EMITTER_H
#define _AUDIO_EMITTER_H

#include <maths/vector4.h>

class AudioEmitter
{
	friend class AudioEmitterComponent;
public:
	AudioEmitter();
	~AudioEmitter();
	void Init(int sfx_id, bool looping = false, class AudioEmitterComponent* ownerComponent = nullptr);
	void SoundStarted(int voice_num);
	void SoundStopped();

	inline bool playing() const { return playing_; }

	inline const gef::Vector4& position() const { return position_;	}
	inline void set_position(const gef::Vector4& position) { position_ = position; }

	inline float radius() const { return radius_; }
	inline void set_radius(float radius) { radius_ = radius; }

	inline int sfx_id() const { return sfx_id_; }
	inline int voice_id() const { return voice_id_; }

	inline bool looping() const { return looping_; }
	inline void set_looping(bool looping) { looping_ = looping; }

	inline bool added_to_audio3d() { return added_to_audio3d_; }
	inline void set_added_to_audio_3d(bool added) { added_to_audio3d_ = added; }

	inline bool to_be_deleted() { return is_to_be_deleted; }
	inline void set_to_be_deleted(bool toDelete) { is_to_be_deleted = toDelete; }
private:
	gef::Vector4 position_;
	bool playing_;
	int voice_id_;
	int sfx_id_;
	float radius_;
	bool looping_;
	bool added_to_audio3d_;
	bool is_to_be_deleted;

	class AudioEmitterComponent* ownerComponent;
};

#endif // _AUDIO_EMITTER_H
