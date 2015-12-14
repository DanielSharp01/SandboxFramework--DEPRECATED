#pragma once

#include "GraphicsDevice.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "../Math/structs.h"

#define SPRITE_BATCH_MAX_SPRITES 60000 / 4
#define SPRITE_BATCH_MAX_VERTICES SPRITE_BATCH_MAX_SPRITES * 4
#define SPRITE_BATCH_MAX_INDICES SPRITE_BATCH_MAX_SPRITES * 6
#define SPRITE_BATCH_VERTEX_SIZE sizeof(BatchVertex)

namespace SandboxFramework
{
	namespace Graphics
	{
		struct BatchVertex
		{
			Math::Vector4 Position;
			Math::Vector4 Color;
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
		public:
			SpriteBatch(GraphicsDevice* graphics);
			~SpriteBatch();

			void Begin();

			void Draw(Math::Vector2 position, Math::Vector2 size, Color color);
			void Draw(Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);

			void End();
		};
	}
}