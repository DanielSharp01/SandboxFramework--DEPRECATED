#pragma once

#include "../Game.h"
#include "../Math/structs.h"
#include "Color.h"
#include "BlendState.h"
#include "DepthTestMode.h"
#include "Viewport.h"
#include "TextureFilter.h"
#include "GLType.h"
#include "ImageFormat.h"


namespace Sand {
	class Game;
	namespace Graphics
	{
		typedef unsigned char BYTE;
		class Shader;
		class VAO;
		class VBO;
		class IBO;
		class Texture2D;

		class GraphicsDevice
		{
			friend Game;
			friend Shader;
			friend VAO;
			friend VBO;
			friend IBO;
			friend Texture2D;
		public:
			GraphicsDevice(Game* game);
			~GraphicsDevice();

			void Clear(Color color);
			void Draw(int indexCount);
			void Draw(VAO* vao, IBO* ibo);

			void SetRenderTarget(Texture2D* texture);
			void SetRenderTargets(Texture2D** textures, unsigned int count);

			void SetBlendFactor(Color color);
			inline Color GetBlendFactor() { return glstate_ConstantColor; }

			void SetDepthTestMode(DepthTestMode mode);
			void SetAlphaTestTreshold(float treshold);
			inline DepthTestMode GetDepthTestMode() { return glstate_DepthTestMode; }
			inline float GetAlphaTestTreshold() { return glstate_AlphaTestTreshold; }

			void SetBlendState(BlendState state);
			void SetBlendState(Blend source, Blend destination);
			inline BlendState GetBlendState() { return glstate_BlendState; }

			inline Viewport& GetViewport() { return m_Viewport; }
		private:
			Game* m_Game;
			Viewport m_Viewport;
			Viewport m_SavedViewport;

			void setViewportSize(unsigned int width, unsigned int height);

			GLuint frameBuffer;

			//OpenGL state management
			Color glstate_ClearColor;
			DepthTestMode glstate_DepthTestMode;
			float glstate_AlphaTestTreshold;
			BlendState glstate_BlendState;
			Color glstate_ConstantColor;
			GLuint glstate_ActiveShaderProgram;
			GLuint glstate_ActiveVAO;
			GLuint glstate_ActiveVBO;
			GLuint glstate_ActiveIBO;
			GLuint glstate_ActiveTexture2D;

			//OpenGL methods for friends:
			GLuint gl_createShaderProgram(std::string vertexSrc, std::string fragmentSrc);
			void gl_bindShader(const Shader* shader);
			void gl_unbindShader(const Shader* shader);
			void gl_destroyShader(Shader* shader);
			
			GLint gl_getLocation(const Shader* shader, std::string uniformName);
			void gl_setUniformInt(GLint location, int value);
			void gl_setUniformIntV(GLint location, int* value, unsigned int count);
			void gl_setUniformFloat(GLint location, float value);
			void gl_setUniformVector2(GLint location, Math::Vector2 vector);
			void gl_setUniformVector3(GLint location, Math::Vector3 vector);
			void gl_setUniformVector4(GLint location, Math::Vector4 vector);
			void gl_setUniformMatrix(GLint location, Math::Matrix matrix);

			GLuint gl_createVAO();
			void gl_bindVAO(const VAO* vao);
			void gl_unbindVAO(const VAO* vao);
			void gl_destroyVAO(VAO* vao);
			void gl_bindVBOToLocation(const VBO* vbo, GLint location, GLType componentType, GLsizei componentCount, GLsizei stride, const GLvoid* offset);

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

			GLuint gl_createTexture2D(BYTE* data, GLsizei width, GLsizei height, ImageFormat imageFormat);
			void gl_setTextureFilters(const Texture2D* texture, TextureFilter minFilter, TextureFilter magFilter);
			void gl_SetActiveTexture(GLuint slot);
			void gl_bindTexture2D(const Texture2D* texture);
			void gl_unbindTexture2D(const Texture2D* texture);
			void gl_destroyTexture2D(Texture2D* texture);
		};
	}
}