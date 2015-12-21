#include "BlendState.h"

namespace Sand
{
	namespace Graphics
	{
		const BlendState BlendState::Alpha = BlendState(Blend::One, Blend::InverseSourceAlpha);
		const BlendState BlendState::Additive = BlendState(Blend::SourceAlpha, Blend::One);
		const BlendState BlendState::NonPremultiplied = BlendState(Blend::SourceAlpha, Blend::InverseSourceAlpha);
		const BlendState BlendState::Opaque = BlendState(Blend::One, Blend::Zero);

		bool BlendState::Equals(const BlendState& b) const
		{
			return Source == b.Source && Destination == b.Destination;
		}

		bool operator==(BlendState a, const BlendState& b)
		{
			return a.Equals(b);
		}

		bool operator!=(BlendState a, const BlendState& b)
		{
			return !(a.Equals(b));
		}
	}
}