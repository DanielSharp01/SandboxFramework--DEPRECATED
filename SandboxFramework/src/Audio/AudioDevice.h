#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#define NULL 0

#include "WaveFile.h"
#include "AudioFormat.h"
#include "PlaybackState.h"

#define AUDIO_SOURCE_MAX 16

namespace Sand
{
	namespace Audio
	{
		class Sound;
		class AudioSource;

		class AudioDevice
		{
			friend Sound;
			friend AudioSource;
		private:
			ALCdevice*  m_Device;
			ALCcontext* m_Context;
			AudioSource* m_Sources[AUDIO_SOURCE_MAX];
		public:
			AudioDevice();
			~AudioDevice();

			inline AudioSource* GetAudioSource(int index) { return m_Sources[index]; }
		private:
			//OpenAL methods for friends
			unsigned int al_createSound(AudioFormat format, const BYTE* data, int dataSize, int sampleRate);
			void al_destroySound(Sound* sound);

			void al_bindSoundToSource(AudioSource* source, const Sound* sound);
			void al_unbindSoundsFromSource(AudioSource* source);
			PlaybackState al_getSourcePlaybackState(const AudioSource* source);
			void al_playSource(AudioSource* source);
			void al_pauseSource(AudioSource* source);
			void al_stopSource(AudioSource* source);
			void al_rewindSource(AudioSource* source);
			bool al_getSourceLooping(const AudioSource* source);
			void al_setSourceLooping(AudioSource* source, bool looping);
			float al_getSourceVolume(const AudioSource* source);
			void al_setSourceVolume(AudioSource* source, float volume);
			float al_getSourceSecOffset(const AudioSource* source);
			void al_setSourceSecOffset(AudioSource* source, float secOffset);
			float al_getSourcePitch(const AudioSource* source);
			void al_setSourcePitch(AudioSource* source, float pitch);
			void al_destroySource(AudioSource* source);
		};
	}
}