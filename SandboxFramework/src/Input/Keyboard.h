#pragma once

#include "KeyboardState.h"

namespace SandboxFramework
{
	class Game;
}

namespace SandboxFramework {
	namespace Input {
		class Keyboard
		{
			friend class SandboxFramework::Game;
		private:
			static KeyboardState actual;
		public:
			inline static KeyboardState GetState() { return actual; }
		private:
			static void setState(int key, bool state);
		};
	}
}