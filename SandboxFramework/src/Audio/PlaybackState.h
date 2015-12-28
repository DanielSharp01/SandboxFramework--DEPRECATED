#pragma once

#include <AL/al.h>

namespace Sand
{
	namespace Audio
	{
		enum PlaybackState
		{
			Initial = AL_INITIAL,
			Playing = AL_PLAYING,
			Paused = AL_PAUSED,
			Stopped = AL_STOPPED
		};
	}
}