#include "AudioSource.h"

namespace Sand
{
	namespace Audio
	{
		AudioSource::AudioSource(AudioDevice* audio, unsigned int id)
			: m_Audio(audio), m_ID(id)
		{ }

		AudioSource::~AudioSource()
		{
			m_Audio->al_destroySource(this);
		}

		void AudioSource::BindSound(const Sound* sound)
		{
			m_Audio->al_bindSoundToSource(this, sound);
		}

		void AudioSource::UnbindSounds()
		{
			m_Audio->al_unbindSoundsFromSource(this);
		}

		PlaybackState AudioSource::GetState() const
		{
			return m_Audio->al_getSourcePlaybackState(this);
		}

		void AudioSource::Play()
		{
			return m_Audio->al_playSource(this);
		}

		void AudioSource::Pause()
		{
			return m_Audio->al_pauseSource(this);
		}

		void AudioSource::Stop()
		{
			return m_Audio->al_stopSource(this);
		}

		void AudioSource::Rewind()
		{
			return m_Audio->al_rewindSource(this);
		}

		float AudioSource::GetVolume() const
		{
			return m_Audio->al_getSourceVolume(this);
		}

		void AudioSource::SetVolume(float volume)
		{
			m_Audio->al_setSourceVolume(this, volume);
		}

		float AudioSource::GetPosition() const
		{
			return m_Audio->al_getSourceSecOffset(this);
		}

		void AudioSource::SetPosition(float position)
		{
			m_Audio->al_setSourceSecOffset(this, position);
		}

		float AudioSource::GetPitch() const
		{
			return m_Audio->al_getSourcePitch(this);
		}

		void AudioSource::SetPitch(float pitch)
		{
			m_Audio->al_setSourcePitch(this, pitch);
		}

		bool AudioSource::GetLooping() const
		{
			return m_Audio->al_getSourceLooping(this);
		}

		void AudioSource::SetLooping(bool looping)
		{
			m_Audio->al_setSourceLooping(this, looping);
		}
	}
}