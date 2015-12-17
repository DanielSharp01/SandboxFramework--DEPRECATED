#pragma once

#include "SpriteBatch.h"

namespace Sand
{
	namespace Graphics
	{
		SpriteBatch::SpriteBatch(GraphicsDevice* graphics)
			: m_Graphics(graphics)
		{
			m_Vao = new VAO(graphics);

			m_Vbo = new VBO(graphics, SPRITE_BATCH_MAX_VERTICES, SPRITE_BATCH_VERTEX_SIZE);
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


			m_Ibo = new IBO(graphics, allIndex, SPRITE_BATCH_MAX_INDICES);
			delete allIndex;

			m_Vao->BindVBOToLocation(m_Vbo, 0, 4, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Position));
			m_Vao->BindVBOToLocation(m_Vbo, 1, 4, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Color));
			m_Vao->BindVBOToLocation(m_Vbo, 2, 2, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, UV));
			m_Vao->BindVBOToLocation(m_Vbo, 3, 1, GL_FLOAT, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, TexID));
			
			m_Textures = new Collections::ArrayList<GLuint>(SPRITE_BATCH_MAX_TEXTURES);
		}

		SpriteBatch::~SpriteBatch()
		{
			delete m_Vbo;
			delete m_Ibo;
			delete m_Vao;
			delete m_Textures;
		}

		void SpriteBatch::Begin()
		{
			m_Pointer = (BatchVertex*)m_Vbo->Map();
			m_SpriteCount = 0;
			m_Textures->Clear();
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color)
		{
			SpriteBatch::Draw(texture, position, size, color, Math::Vector2(0, 0), 0, Math::Vector2(1, 1));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			SpriteBatch::Draw(texture, position, size, color, origin, rotation, Math::Vector2(scale, scale));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Vector2 position, Math::Vector2 size, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
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

			float texID = -1;

			if (texture)
			{
				int i;
				for (i = 0; i < m_Textures->GetCount() && texture->m_ID != (*m_Textures)[i]; i++);

				if (i < m_Textures->GetCount()) texID = i;
				else
				{
					if (m_Textures->GetCount() == SPRITE_BATCH_MAX_TEXTURES)
					{
						End();
						Begin();
						m_Textures->Clear();
					}
					m_Textures->Add(texture->m_ID);
					texture->BindToActive(m_Textures->GetCount() - 1);
					texID = m_Textures->GetCount() - 1;
				}
			}

			m_Pointer->Position = topLeft;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(0, 1);
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = topRight;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(1, 1);
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = bottomRight;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(1, 0);
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = bottomLeft;
			m_Pointer->Color = colour;
			m_Pointer->UV = Math::Vector2(0, 0);
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_SpriteCount++;
		}

		void SpriteBatch::End()
		{
			m_Vbo->Unmap();
			m_Vao->Bind();
			m_Ibo->Bind();

			//std::cout << m_SpriteCount << std::endl;

			m_Graphics->Draw(m_SpriteCount * 6);
		}
	}
}