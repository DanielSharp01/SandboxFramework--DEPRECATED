#pragma once

#include "MouseButtons.h"
#include "../Math/Vector2.h"

#define MAX_BUTTONS GLFW_MOUSE_BUTTON_LAST

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
			inline bool IsButtonDown(MouseButtons key) { return m_States[key]; }
			inline bool IsButtonUp(MouseButtons key) { return !m_States[key]; }

			inline Math::Vector2 GetPosition() { return m_Position; }
			inline Math::Vector2 GetScroll() { return m_Scroll; }
		};
	}
}