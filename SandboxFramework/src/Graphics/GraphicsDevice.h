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
#include "Bitmap.h"


namespace Sand {
	class Game;
	namespace Graphics
	{
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
			void SetRenderTargets(Texture2D** textures, unsigned short count);

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

			void setViewportSize(unsigned short width, unsigned short height);

			unsigned int frameBuffer;

			//OpenGL state management
			Color glstate_ClearColor;
			DepthTestMode glstate_DepthTestMode;
			float glstate_AlphaTestTreshold;
			BlendState glstate_BlendState;
			Color glstate_ConstantColor;
			unsigned int glstate_ActiveShaderProgram;
			unsigned int glstate_ActiveVAO;
			unsigned int glstate_ActiveVBO;
			unsigned int glstate_ActiveIBO;
			unsigned int glstate_ActiveTexture2D;

			//OpenGL methods for friends:
			unsigned int gl_createShaderProgram(std::string vertexSrc, std::string fragmentSrc);
			void gl_bindShader(const Shader* shader);
			void gl_unbindShader(const Shader* shader);
			void gl_destroyShader(Shader* shader);
			
			int gl_getLocation(const Shader* shader, std::string uniformName);
			void gl_setUniformInt(int location, int value);
			void gl_setUniformIntV(int location, int* value, unsigned int count);
			void gl_setUniformFloat(int location, float value);
			void gl_setUniformVector2(int location, Math::Vector2 vector);
			void gl_setUniformVector3(int location, Math::Vector3 vector);
			void gl_setUniformVector4(int location, Math::Vector4 vector);
			void gl_setUniformMatrix(int location, Math::Matrix matrix);

			unsigned int gl_createVAO();
			void gl_bindVAO(const VAO* vao);
			void gl_unbindVAO(const VAO* vao);
			void gl_destroyVAO(VAO* vao);
			void gl_bindVBOToLocation(const VBO* vbo, int location, GLType componentType, int componentCount, int stride, const void* offset);

			unsigned int gl_createVBO(int maxSize);
			unsigned int gl_createVBO(void* data, int size);
			void gl_bindVBO(const VBO* vbo);
			void gl_unbindVBO(const VBO* vbo);
			void gl_destroyVBO(VBO* vbo);
			void* gl_mapVBO(VBO* vbo);
			void gl_unmapVBO(VBO* vbo);

			unsigned int gl_createIBO(GLushort* indices, unsigned int count);
			void gl_bindIBO(const IBO* vbo);
			void gl_unbindIBO(const IBO* ibo);
			void gl_destroyIBO(IBO* vbo);

			unsigned int gl_createTexture2D(BYTE* data, unsigned short width, unsigned short height, ImageFormat imageFormat);
			void gl_setTextureFilters(const Texture2D* texture, TextureFilter minFilter, TextureFilter magFilter);
			void gl_SetActiveTexture(unsigned short slot);
			void gl_bindTexture2D(const Texture2D* texture);
			void gl_unbindTexture2D(const Texture2D* texture);
			void gl_destroyTexture2D(Texture2D* texture);
			Bitmap* gl_getTexture2DAsBitmap(const Texture2D* texture);
			void gl_setTexture2D(Texture2D* texture, BYTE* data, unsigned short width, unsigned short height, ImageFormat format);
			void gl_setSubTexture2D(Texture2D* texture, BYTE* data, unsigned short x, unsigned short y, unsigned short width, unsigned short height, ImageFormat format);
		};
	}
}