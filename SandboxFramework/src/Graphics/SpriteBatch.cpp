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

			m_Vao->BindVBOToLocation(m_Vbo, 0, 4, GLType::Float, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Position));
			m_Vao->BindVBOToLocation(m_Vbo, 1, 4, GLType::Float, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, Color));
			m_Vao->BindVBOToLocation(m_Vbo, 2, 2, GLType::Float, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, UV));
			m_Vao->BindVBOToLocation(m_Vbo, 3, 1, GLType::Float, sizeof(BatchVertex), (const GLvoid*)offsetof(BatchVertex, TexID));
			
			m_Textures = new Collections::ArrayList<GLuint>(SPRITE_BATCH_MAX_TEXTURES);
		}

		SpriteBatch::~SpriteBatch()
		{
			delete m_Vbo;
			delete m_Ibo;
			delete m_Vao;
			delete m_Textures;
		}

		void SpriteBatch::Begin(Shader* shader)
		{
			m_Shader = shader;
			m_Pointer = (BatchVertex*)m_Vbo->Map();
			m_SpriteCount = 0;
			m_Textures->Clear();
		}

		void SpriteBatch::Draw(Math::Rectangle destination, Color color)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), destination, color, Math::Matrix::Identity());
		}

		void SpriteBatch::Draw(Math::Rectangle destination, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), destination, color, Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale, scale, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Math::Rectangle destination, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), destination, color, Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale.X, scale.Y, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Math::Rectangle destination, Color color, Math::Matrix matrix)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), destination, color, matrix);
		}

		void SpriteBatch::Draw(Math::Rectangle area, Math::Vector2 position, Color color)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), area, color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Math::Rectangle area, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), area, color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f))
				* Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale, scale, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Math::Rectangle area, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), area, color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f))
				* Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale.X, scale.Y, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Math::Rectangle area, Math::Vector2 position, Color color, Math::Matrix matrix)
		{
			Draw(NULL, Math::Rectangle(0, 0, 0, 0), area, color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f)) * matrix);
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle destination, Color color)
		{
			Draw(texture, Math::Rectangle(0, 0, 0, 0), destination, color, Math::Matrix::Identity());
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Rectangle destination, Color color)
		{
			Draw(texture, source, destination, color, Math::Matrix::Identity());
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Rectangle destination, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			Draw(texture, source, destination, color, Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale, scale, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}
		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Rectangle destination, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
		{
			Draw(texture, source, destination, color, Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale.X, scale.Y, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Vector2 position, Color color)
		{
			Draw(texture, Math::Rectangle(0, 0, 0, 0), Math::Rectangle(0, 0, texture->GetWidth() / texDivisor(), texture->GetHeight() / texDivisor()), color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Vector2 position, Color color)
		{
			Draw(texture, source, Math::Rectangle(0, 0, texture->GetWidth() / texDivisor(), texture->GetHeight() / texDivisor()), color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, float scale)
		{
			Draw(texture, Math::Rectangle(0, 0, 0, 0), Math::Rectangle(0, 0, texture->GetWidth() / texDivisor(), texture->GetHeight() / texDivisor()), color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f))
				* Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale, scale, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Vector2 position, Color color, Math::Vector2 origin, float rotation, Math::Vector2 scale)
		{
			Draw(texture, Math::Rectangle(0, 0, 0, 0), Math::Rectangle(0, 0, texture->GetWidth() / texDivisor(), texture->GetHeight() / texDivisor()), color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f))
				* Math::Matrix::Rotation(rotation, Math::Vector3(0, 0, 1))
				* Math::Matrix::Scale(Math::Vector3(scale.X, scale.Y, 1.0f))
				* Math::Matrix::Translation(Math::Vector3(-origin.X, -origin.Y, 0.0f)));
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Vector2 position, Color color, Math::Matrix matrix)
		{
			Draw(texture, Math::Rectangle(0, 0, 0, 0), Math::Rectangle(0, 0, texture->GetWidth() / texDivisor(), texture->GetHeight() / texDivisor()), color, Math::Matrix::Translation(Math::Vector3(position.X, position.Y, 0.0f)) * matrix);
		}

		void SpriteBatch::Draw(Texture2D* texture, Math::Rectangle source, Math::Rectangle destination, Color color, Math::Matrix matrix)
		{
			destination.Transform(matrix);

			if (source.GetArea() == 0)
			{
				source = Math::Rectangle(0, 0, 1, 1);
			}
			else
			{
				//TODO: Move this operation inside rectangle
				source.TopLeft /= Math::Vector2(texture->GetWidth() ,texture->GetHeight());
				source.TopRight /= Math::Vector2(texture->GetWidth(), texture->GetHeight());
				source.BottomLeft /= Math::Vector2(texture->GetWidth(), texture->GetHeight());
				source.BottomRight /= Math::Vector2(texture->GetWidth(), texture->GetHeight());
			}

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
						Begin(m_Shader);
						m_Textures->Clear();
					}
					m_Textures->Add(texture->m_ID);
					texture->BindToActive(m_Textures->GetCount() - 1);
					texID = m_Textures->GetCount() - 1;
				}
			}

			m_Pointer->Position = Math::Vector4(destination.TopLeft.X, destination.TopLeft.Y, 0, 1);
			m_Pointer->Color = colour;
			m_Pointer->UV = source.BottomLeft;
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = Math::Vector4(destination.TopRight.X, destination.TopRight.Y, 0, 1);
			m_Pointer->Color = colour;
			m_Pointer->UV = source.BottomRight;
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = Math::Vector4(destination.BottomRight.X, destination.BottomRight.Y, 0, 1);
			m_Pointer->Color = colour;
			m_Pointer->UV = source.TopRight;
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_Pointer->Position = Math::Vector4(destination.BottomLeft.X, destination.BottomLeft.Y, 0, 1);
			m_Pointer->Color = colour;
			m_Pointer->UV = source.TopLeft;
			m_Pointer->TexID = texID;
			m_Pointer++;

			m_SpriteCount++;
		}

		void SpriteBatch::End()
		{
			m_Shader->Bind();
			m_Shader->SetUniformDefaultIntV("textures", 32);
			m_Shader->SetUniformMatrix("proj", m_Graphics->GetViewport().GetOrthoProjectionMatrix());
			m_Vbo->Unmap();
			m_Vao->Bind();
			m_Ibo->Bind();

			//std::cout << m_SpriteCount << std::endl;

			m_Graphics->Draw(m_SpriteCount * 6);
		}

		float SpriteBatch::texDivisor()
		{
			return (m_Graphics->GetViewport().GetWidth() / m_Graphics->GetViewport().GetProjectedWidth());
		}
	}
}