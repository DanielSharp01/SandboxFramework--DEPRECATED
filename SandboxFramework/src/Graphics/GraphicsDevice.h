#pragma once

#include "../Game.h"
#include "Color.h"
#include "Shader.h"

namespace SandboxFramework {
	namespace Graphics
	{
		class GraphicsDevice
		{
		public:
			GraphicsDevice(Game* game);
			~GraphicsDevice();

			void Clear(Color color);

			Shader* CreateShader(std::string vertexPath, std::string fragmentPath);
			void DestroyShader(Shader* shader);
			void UseShader(Shader* shader);
		private:
			Game* m_Game;

			//OpenGL state management
			GLuint gl_ActiveProgram;
			Color gl_ClearColor;
		};
	}
}