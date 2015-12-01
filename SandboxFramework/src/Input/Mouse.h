#pragma once

#include "MouseState.h"

namespace SandboxFramework
{
	class Game;
}

namespace SandboxFramework {
	namespace Input {
		class Mouse
		{
			friend class SandboxFramework::Game;
		private:
			static MouseState actual;
		public:
			inline static MouseState GetState() { return actual; }
		private:
			static void setButtonState(int button, bool state);
			static void setCursorState(float x, float y);
			static void setScrollState(float x, float y);
		};
	}
}