#pragma once

#include "VAO.h"
#include "VBO.h"

namespace Sand {
	namespace Graphics {
		VAO::VAO(GraphicsDevice* graphics)
			: m_Graphics(graphics)
		{
			m_VBOLocations = new Collections::Dictionary<VBO*, Collections::ArrayList<VBOLocation>*>();
			m_ID = m_Graphics->gl_createVAO();
		}

		VAO::~VAO()
		{
			for (int i = 0; i < m_VBOLocations->GetCount(); i++)
			{
				VBO* vbo = m_VBOLocations->GetKeys()->Get(i);
				delete (m_VBOLocations->RemoveAt(vbo));
				delete vbo;
			}

			m_Graphics->gl_destroyVAO(this);
		}

		void VAO::BindVBOToLocation(VBO* vbo, GLint location, GLint componentCount, GLType componentType, GLint stride, const GLvoid* offset)
		{
			if (m_VBOLocations->ContainsKey(vbo))
			{
				m_VBOLocations->Get(vbo)->Add(location);
			}
			else
			{
				m_VBOLocations->Add(vbo, new Collections::ArrayList<VBOLocation>());
				m_VBOLocations->Get(vbo)->Add(location);
			}

			Bind();
			m_Graphics->gl_bindVBOToLocation(vbo, location, componentType, componentCount, stride, offset);
		}

		void VAO::Bind() const
		{
			m_Graphics->gl_bindVAO(this);
		}

		void VAO::Unbind() const
		{
			m_Graphics->gl_unbindVAO(this);
		}
	}
}