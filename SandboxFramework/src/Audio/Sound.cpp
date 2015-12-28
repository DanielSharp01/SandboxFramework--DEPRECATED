#include "Sound.h"

namespace Sand
{
	namespace Audio
	{
		Sound::Sound(AudioDevice* audio, WaveFile* wav)
			: m_Audio(audio)
		{
			m_ID = m_Audio->al_createSound(wav->GetFormat(), wav->GetData(), wav->GetDataSize(), wav->GetSampleRate());
			int lengthInSamples = wav->GetDataSize() * 8 / (wav->GetChannelNumber() * wav->GetBitsPerSample());
			m_Duration = (float)lengthInSamples / (float)wav->GetSampleRate();
		}
		
		Sound::~Sound()
		{
			m_Audio->al_destroySound(this);
		}
	}
}