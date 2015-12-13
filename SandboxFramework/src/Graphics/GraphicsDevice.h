#pragma once

#include "../Game.h"
#include "../Math/structs.h"
#include "Color.h"

namespace SandboxFramework {
	namespace Graphics
	{
		class Shader;
		class VAO;
		class VBO;
		class IBO;

		class GraphicsDevice
		{
			friend Shader;
			friend VAO;
			friend VBO;
			friend IBO;
		public:
			GraphicsDevice(Game* game);
			~GraphicsDevice();

			void Clear(Color color);
			void Draw(int indexCount);
			void Draw(VAO* vao, IBO* ibo);
		private:
			Game* m_Game;

			//OpenGL state management
			GLuint glstate_ActiveShaderProgram;
			GLuint glstate_ActiveVAO;
			GLuint glstate_ActiveVBO;
			GLuint glstate_ActiveIBO;
			Color glstate_ClearColor;

			//OpenGL methods for friends:
			GLuint gl_createShaderProgram(std::string vertexSrc, std::string fragmentSrc);
			void gl_bindShader(const Shader* shader);
			void gl_unbindShader(const Shader* shader);
			void gl_destroyShader(Shader* shader);

			GLuint gl_createVAO();
			void gl_bindVAO(const VAO* vao);
			void gl_unbindVAO(const VAO* vao);
			void gl_destroyVAO(VAO* vao);
			void gl_bindVBOToLocation(const VBO* vbo, GLint location, GLenum componentType, GLsizei componentCount, GLsizei stride, const GLvoid* offset);

			GLuint gl_createVBO(GLsizei maxSize);
			GLuint gl_createVBO(GLvoid* data, GLsizei size);
			void gl_bindVBO(const VBO* vbo);
			void gl_unbindVBO(const VBO* vbo);
			void gl_destroyVBO(VBO* vbo);
			GLvoid* gl_mapVBO(VBO* vbo);
			void gl_unmapVBO(VBO* vbo);

			GLuint gl_createIBO(GLushort* indices, GLsizei count);
			void gl_bindIBO(const IBO* vbo);
			void gl_unbindIBO(const IBO* ibo);
			void gl_destroyIBO(IBO* vbo);


			GLint gl_getLocation(const Shader* shader, std::string uniformName);
			void gl_setUniformInt(GLint location, int value);
			void gl_setUniformFloat(GLint location, float value);
			void gl_setUniformVector2(GLint location, Math::Vector2 vector);
			void gl_setUniformVector3(GLint location, Math::Vector3 vector);
			void gl_setUniformVector4(GLint location, Math::Vector4 vector);
			void gl_setUniformMatrix(GLint location, Math::Matrix matrix);
		};
	}
}