#include "AudioDevice.h"
#include "Sound.h"
#include "AudioSource.h"

namespace Sand
{
	namespace Audio
	{
		AudioDevice::AudioDevice()
		{
			m_Device = alcOpenDevice(NULL);
			if (!m_Device)
			{
				std::cout << "Failed to initialize OpenAL!" << std::endl;
				return;
			}
			m_Context = alcCreateContext(m_Device, NULL);
			if (!m_Context)
			{
				std::cout << "Failed to initialize OpenAL!" << std::endl;
				return;
			}

			alcMakeContextCurrent(m_Context);
			unsigned int* ids = new unsigned int[AUDIO_SOURCE_MAX];
			alGenSources(AUDIO_SOURCE_MAX, ids);
			for (int i = 0; i < AUDIO_SOURCE_MAX; i++)
			{
				m_Sources[i] = new AudioSource(this, ids[i]);
			}
			delete ids;
		}

		AudioDevice::~AudioDevice()
		{
			for (int i = 0; i < AUDIO_SOURCE_MAX; i++)
			{
				delete m_Sources[i];
			}

			if (m_Context) alcDestroyContext(m_Context);
			if (m_Device) alcCloseDevice(m_Device);
		}

		unsigned int AudioDevice::al_createSound(AudioFormat format, const BYTE* data, int dataSize, int sampleRate)
		{
			unsigned int ret;
			alGenBuffers(1, &ret);
			alBufferData(ret, format, data, dataSize, sampleRate);
			return ret;
		}

		void AudioDevice::al_destroySound(Sound* sound)
		{
			alDeleteBuffers(1, &sound->m_ID);
		}

		void AudioDevice::al_bindSoundToSource(AudioSource* source, const Sound* sound)
		{
			alSourcei(source->m_ID, AL_BUFFER, sound->m_ID);
			source->m_Sound = sound;
		}

		void AudioDevice::al_unbindSoundsFromSource(AudioSource* source)
		{
			alSourcei(source->m_ID, AL_BUFFER, NULL);
			source->m_Sound = NULL;
		}

		PlaybackState AudioDevice::al_getSourcePlaybackState(const AudioSource* source)
		{
			int ret;
			alGetSourcei(source->m_ID, AL_SOURCE_STATE, &ret);
			return (PlaybackState)ret;
		}

		void AudioDevice::al_playSource(AudioSource* source)
		{
			alSourcePlay(source->m_ID);
		}

		void AudioDevice::al_pauseSource(AudioSource* source)
		{
			alSourcePause(source->m_ID);
		}

		void AudioDevice::al_stopSource(AudioSource* source)
		{
			alSourceStop(source->m_ID);
		}

		void AudioDevice::al_rewindSource(AudioSource* source)
		{
			alSourceRewind(source->m_ID);
		}

		bool AudioDevice::al_getSourceLooping(const AudioSource* source)
		{
			int ret;
			alGetSourcei(source->m_ID, AL_LOOPING, &ret);
			return ret;
		}

		void AudioDevice::al_setSourceLooping(AudioSource* source, bool looping)
		{
			alSourcei(source->m_ID, AL_LOOPING, looping);
		}

		float AudioDevice::al_getSourceVolume(const AudioSource* source)
		{
			float ret;
			alGetSourcef(source->m_ID, AL_GAIN, &ret);
			return ret;
		}

		void AudioDevice::al_setSourceVolume(AudioSource* source, float volume)
		{
			alSourcef(source->m_ID, AL_GAIN, volume);
		}

		float AudioDevice::al_getSourceSecOffset(const AudioSource* source)
		{
			float ret;
			alGetSourcef(source->m_ID, AL_SEC_OFFSET, &ret);
			return ret;
		}

		void AudioDevice::al_setSourceSecOffset(AudioSource* source, float secOffset)
		{
			alSourcef(source->m_ID, AL_SEC_OFFSET, secOffset);
		}

		float AudioDevice::al_getSourcePitch(const AudioSource* source)
		{
			float ret;
			alGetSourcef(source->m_ID, AL_PITCH, &ret);
			return ret;
		}

		void AudioDevice::al_setSourcePitch(AudioSource* source, float pitch)
		{
			alSourcef(source->m_ID, AL_PITCH, pitch);
		}

		void AudioDevice::al_destroySource(AudioSource* source)
		{
			if (source->m_Sound != NULL) al_unbindSoundsFromSource(source);
			alDeleteSources(1, &source->m_ID);
		}
	}
}