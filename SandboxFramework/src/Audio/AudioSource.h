#pragma once

#include "AudioDevice.h"
#include "Sound.h"
#include "PlaybackState.h"

namespace Sand
{
	namespace Audio
	{
		class AudioSource
		{
			friend AudioDevice;
		private:
			AudioDevice* m_Audio;
			const Sound* m_Sound;
			unsigned int m_ID;
		public:
			AudioSource(AudioDevice* audio, unsigned int id);
			~AudioSource();

			void BindSound(const Sound* sound);
			void UnbindSounds();

			PlaybackState GetState() const;
			
			void Play();
			void Pause();
			void Stop();
			void Rewind();

			float GetVolume() const;
			void SetVolume(float volume);

			inline float GetDuration() { return m_Sound->GetDuration(); }
			float GetPosition() const;
			void SetPosition(float position);

			float GetPitch() const;
			void SetPitch(float pitch);

			bool GetLooping() const;
			void SetLooping(bool looping);

		};
	}
}