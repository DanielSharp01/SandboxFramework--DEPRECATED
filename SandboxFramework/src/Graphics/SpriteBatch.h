#pragma once

#include "GraphicsDevice.h"
#include "Texture2D.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "../Math/structs.h"
#include "../Collections/ArrayList.h"

#define SPRITE_BATCH_MAX_SPRITES 60000 / 4
#define SPRITE_BATCH_MAX_VERTICES SPRITE_BATCH_MAX_SPRITES * 4
#define SPRITE_BATCH_MAX_INDICES SPRITE_BATCH_MAX_SPRITES * 6
#define SPRITE_BATCH_VERTEX_SIZE sizeof(BatchVertex)
#define SPRITE_BATCH_MAX_TEXTURES 32

//TODO: Move shader inside
namespace SandboxFramework
{
	namespace Graphics
	{
		struct BatchVertex
		{
			Math::Vector4 Position;
			Math::Vector4 Color;
			Math::Vector2 UV;
			float TexID;
		};

		class SpriteBatch
		{
		private:
			GraphicsDevice* m_Graphics;
			VAO* vao;
			VBO* vbo;
			IBO* ibo;
			BatchVertex* m_Pointer;
			int m_SpriteCount;
			Collections::ArrayList<GLuint> textures;
		public:
			SpriteBatch(GraphicsDevice* graphics);
			~SpriteBatch();

			void Begin();

			//TODO: Support only color (method you can pass NULL for no tex)

			void Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color);
			void Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);

			void End();
		};
	}
}