#pragma once

#include "../Math/Vector2.h"

#define MAX_BUTTONS 16

namespace SandboxFramework {
	namespace Input {
		struct MouseState
		{
			friend class Mouse;
		private:
			bool states[MAX_BUTTONS];

			Math::Vector2 position;
			Math::Vector2 scroll;
		public:
			inline bool IsButtonDown(int key) { return states[key]; }
			inline bool IsButtonUp(int key) { return !states[key]; }

			//TODO: Implement convenient mouse buttons

			inline Math::Vector2 GetPosition() { return position; }
			inline Math::Vector2 GetScroll() { return scroll; }
		};
	}
}