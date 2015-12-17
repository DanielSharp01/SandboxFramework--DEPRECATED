#pragma once

#include "../Math/Vector2.h"

#define MAX_BUTTONS 16

namespace Sand {
	namespace Input {
		struct MouseState
		{
			friend class Mouse;
		private:
			bool m_States[MAX_BUTTONS];

			Math::Vector2 m_Position;
			Math::Vector2 m_Scroll;
		public:
			inline bool IsButtonDown(int key) { return m_States[key]; }
			inline bool IsButtonUp(int key) { return !m_States[key]; }

			//TODO: Implement convenient mouse buttons

			inline Math::Vector2 GetPosition() { return m_Position; }
			inline Math::Vector2 GetScroll() { return m_Scroll; }
		};
	}
}