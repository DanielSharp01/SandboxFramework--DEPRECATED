#pragma once

#include "GraphicsDevice.h"
#include "Texture2D.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Rectangle.h"
#include "../Math/structs.h"
#include "../Collections/ArrayList.h"

#define SPRITE_BATCH_MAX_SPRITES 60000 / 4
#define SPRITE_BATCH_MAX_VERTICES SPRITE_BATCH_MAX_SPRITES * 4
#define SPRITE_BATCH_MAX_INDICES SPRITE_BATCH_MAX_SPRITES * 6
#define SPRITE_BATCH_VERTEX_SIZE sizeof(BatchVertex)
#define SPRITE_BATCH_MAX_TEXTURES 32

//TODO: Move shader inside
namespace Sand
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
			VAO* m_Vao;
			VBO* m_Vbo;
			IBO* m_Ibo;
			BatchVertex* m_Pointer;
			int m_SpriteCount;
			Collections::ArrayList<GLuint>* m_Textures;
			float m_TexDivisor; //TODO: Remove and think of a better way (basically probably just set the viewport)
		public:
			SpriteBatch(GraphicsDevice* graphics);
			~SpriteBatch();

			void SetTextureDimensionDivisor(float divisor);

			void Begin();

			void Draw(Rectangle destination, Color color);
			void Draw(Rectangle destination, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Rectangle destination, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);
			void Draw(Rectangle destination, Color color, Math::Matrix matrix);

			void Draw(Rectangle area, Math::Vector2 position, Color color);
			void Draw(Rectangle area, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Rectangle area, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);
			void Draw(Rectangle area, Math::Vector2 position, Color color, Math::Matrix matrix);

			void Draw(Texture2D* texture, Rectangle destination, Color color);
			void Draw(Texture2D* texture, Rectangle source, Rectangle destination, Color color);
			void Draw(Texture2D* texture, Rectangle source, Rectangle destination, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Texture2D* texture, Rectangle source, Rectangle destination, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);
			void Draw(Texture2D* texture, Rectangle source, Rectangle destination, Color color, Math::Matrix matrix);

			void Draw(Texture2D* texture, Math::Vector2 position, Color color);
			void Draw(Texture2D* texture, Rectangle source, Math::Vector2 position, Color color);
			void Draw(Texture2D* texture, Rectangle source, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, float scale);
			void Draw(Texture2D* texture, Rectangle source, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale);
			void Draw(Texture2D* texture, Rectangle source, Math::Vector2 position, Color color, Math::Matrix matrix);

			void End();
		};
	}
}