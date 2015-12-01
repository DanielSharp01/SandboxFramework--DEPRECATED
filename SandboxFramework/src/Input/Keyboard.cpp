#include "Keyboard.h"

namespace SandboxFramework {
	namespace Input {

		KeyboardState Keyboard::actual = KeyboardState();

		void Keyboard::setState(int key, bool state)
		{
			Keyboard::actual.states[key] = state;
		}
	}
}