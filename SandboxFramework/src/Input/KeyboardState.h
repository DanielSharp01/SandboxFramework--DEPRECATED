#pragma once

#include "Keys.h"
#define MAX_KEYS GLFW_KEY_LAST

namespace Sand {
	namespace Input {
		class KeyboardState
		{
			friend class Keyboard;
		private:
			bool m_States[MAX_KEYS];
		public:
			inline bool IsKeyDown(Keys key) { return m_States[key]; }
			inline bool IsKeyUp(Keys key) { return !m_States[key]; }
		};
	}
}