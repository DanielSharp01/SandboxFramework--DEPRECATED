#pragma once

#include "Blend.h"

namespace Sand
{
	namespace Graphics
	{
		struct BlendState
		{
			static const BlendState Alpha;
			static const BlendState Additive;
			static const BlendState NonPremultiplied;
			static const BlendState Opaque;

			Blend Source;
			Blend Destination;

#ifdef VISUAL_SCHOOL
			BlendState() : Source(Blend::One), Destination(Blend::One) {}
#else
			BlendState() = default;
#endif

			BlendState(Blend source, Blend destination)
				: Source(source), Destination(destination) {}

			bool Equals(const BlendState& b) const;

			friend bool operator==(BlendState a, const BlendState& b);
			friend bool operator!=(BlendState a, const BlendState& b);
		};
	}
}