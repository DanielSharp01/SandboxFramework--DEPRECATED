#pragma once

#include "AudioDevice.h"

namespace Sand
{
	namespace Audio
	{
		class Sound
		{
			friend AudioDevice;
		private:
			AudioDevice* m_Audio;
			unsigned int m_ID;
			float m_Duration;
		public:
			Sound(AudioDevice* audio, WaveFile* wav);
			~Sound();

			inline float GetDuration() const { return m_Duration; }
		};
	}
}