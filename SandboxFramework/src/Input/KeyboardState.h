#pragma once

#define MAX_KEYS 512

namespace Sand {
	namespace Input {
		class KeyboardState
		{
			friend class Keyboard;
		private:
			bool m_States[MAX_KEYS];
		public:
			inline bool IsKeyDown(int key) { return m_States[key]; }
			inline bool IsKeyUp(int key) { return !m_States[key]; }
		};
	}
}