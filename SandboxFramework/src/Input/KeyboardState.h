#pragma once

#define MAX_KEYS 512

namespace SandboxFramework {
	namespace Input {
		class KeyboardState
		{
			friend class Keyboard;
		private:
			bool states[MAX_KEYS];
		public:
			inline bool IsKeyDown(int key) { return states[key]; }
			inline bool IsKeyUp(int key) { return !states[key]; }
		};
	}
}