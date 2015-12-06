#pragma once

#include "../Game.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix.h"
#include "Color.h"

namespace SandboxFramework {
	namespace Graphics
	{
		class Shader;
		
		class GraphicsDevice
		{
			friend Shader;
		public:
			GraphicsDevice(Game* game);
			~GraphicsDevice();

			void Clear(Color color);
		private:
			Game* m_Game;

			//OpenGL state management
			GLuint glstate_ActiveProgram;
			Color glstate_ClearColor;

			//OpenGL methods for friends:
			GLuint gl_createShaderProgram(std::string vertexSrc, std::string fragmentSrc);
			void gl_bindShader(Shader* shader);
			void gl_destroyShader(Shader* shader);

			GLint gl_getLocation(Shader* shader, std::string uniformName);
			void gl_setUniformInt(GLint location, int value);
			void gl_setUniformFloat(GLint location, float value);
			void gl_setUniformVector2(GLint location, Math::Vector2 vector);
			void gl_setUniformVector3(GLint location, Math::Vector3 vector);
			void gl_setUniformVector4(GLint location, Math::Vector4 vector);
			void gl_setUniformMatrix(GLint location, Math::Matrix matrix);
		};
	}
}