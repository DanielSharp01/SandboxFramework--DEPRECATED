#pragma once

#include "SpriteBatch.h"

namespace SandboxFramework
{
	namespace Graphics
	{
		SpriteBatch::SpriteBatch(GraphicsDevice* graphics)
			: m_Graphics(graphics)
		{
			vao = new VAO(graphics);

			vbo = new VBO(graphics, SPRITE_BATCH_MAX_VERTICES, SPRITE_BATCH_VERTEX_SIZE);
			GLushort* allIndex = new GLushort[SPRITE_BATCH_MAX_INDICES];

			int bitch = SPRITE_BATCH_MAX_SPRITES;
			int j = 0;
			for (int i = 0; i < bitch; i++)
			{
				allIndex[  j  ] = i * 4 + 0;
				allIndex[j + 1] = i * 4 + 1;
				allIndex[j + 2] = i * 4 + 2;
				allIndex[j + 3] = i * 4 + 2;
				allIndex[j + 4] = i * 4 + 3;
				allIndex[j + 5] = i * 4 + 0;

				j += 6;
			}


			ibo = new IBO(graphics, allIndex, SPRITE_BATCH_MAX_INDICES);
			delete allIndex;

			vao->BindVBOToLocation(vbo, 1, 4, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Position));
			vao->BindVBOToLocation(vbo, 0, 4, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Color));
			vao->BindVBOToLocation(vbo, 3, 2, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, UV));
			vao->BindVBOToLocation(vbo, 2, 1, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, TexID));
		}

		SpriteBatch::~SpriteBatch()
		{
			delete vbo;
			delete ibo;
			delete vao;
		}

		void SpriteBatch::Begin()
		{
			m_Pointer = (BatchVertex*)vbo->Map();
			m_SpriteCount = 0;
		}

		void SpriteBatch::Draw(Math::Vector2 position, Math::Vector2 size, Color color)
		{
			SpriteBatch::Draw(position, size, color, Math::Vector2(0, 0), 0, Math::Vector2(1, 1));
		}

		void SpriteBatch::Draw(Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			SpriteBatch::Draw(position, size, color, origin, rotation, Math::Vector2(scale, scale));
		}

		void SpriteBatch::Draw(Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
		{
			Math::Matrix model = Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f))
									* Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
									* Math::Matrix::Scale(Math::Vector3(scale.X, scale.Y, 1.0f))
									* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f));

			Math::Vector4 topLeft = Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f).Transform(model);
			Math::Vector4 topRight = Math::Vector4(size.X, 0.0f, 0.0f, 1.0f).Transform(model);
			Math::Vector4 bottomRight = Math::Vector4(size.X, size.Y, 0.0f, 1.0f).Transform(model);
			Math::Vector4 bottomLeft = Math::Vector4(0.0f, size.Y, 0.0f, 1.0f).Transform(model);

			Math::Vector4 colour = color.ToVector4();

			m_Pointer->Position = topLeft;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(0, 1);
			m_Pointer->TexID = 0;
			m_Pointer++;

			m_Pointer->Position = topRight;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(1, 1);
			m_Pointer->TexID = 0;
			m_Pointer++;

			m_Pointer->Position = bottomRight;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(1, 0);
			m_Pointer->TexID = 1;
			m_Pointer++;

			m_Pointer->Position = bottomLeft;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(0, 0);
			m_Pointer->TexID = 1;
			m_Pointer++;

			m_SpriteCount++;
		}

		void SpriteBatch::End()
		{
			vbo->Unmap();
			vao->Bind();
			ibo->Bind();

			//std::cout << m_SpriteCount << std::endl;

			m_Graphics->Draw(m_SpriteCount * 6);
		}
	}
}