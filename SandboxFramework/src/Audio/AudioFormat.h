#pragma once

#include <AL/al.h>

namespace Sand
{
	namespace Audio
	{
		enum AudioFormat
		{
			Mono8 = AL_FORMAT_MONO8,
			Mono16 = AL_FORMAT_MONO16,
			Stereo8 = AL_FORMAT_STEREO8,
			Stereo16 = AL_FORMAT_STEREO16
		};
	}
}