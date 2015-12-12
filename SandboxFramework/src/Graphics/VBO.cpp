#include "VBO.h"

#include "GraphicsDevice.h"

namespace SandboxFramework {
	namespace Graphics {
		VBO::VBO(GraphicsDevice* graphics, GLfloat* vertices, GLsizei count, GLsizei componentCount)
			: m_Graphics(graphics), m_Count(count), m_ComponentCount(componentCount)
		{
			m_ID = m_Graphics->gl_createVBO(vertices, m_Count, m_ComponentCount);
		}

		VBO::VBO(GraphicsDevice* graphics, GLsizei maxVertices, GLsizei componentCount)
		{
			m_ID = m_Graphics->gl_createVBO(maxVertices * componentCount * sizeof(GLfloat));
		}

		VBO::~VBO()
		{
			m_Graphics->gl_destroyVBO(this);
		}

		GLvoid* VBO::Map()
		{
			return m_Graphics->gl_mapVBO(this);
		}

		void VBO::Unmap()
		{
			m_Graphics->gl_unmapVBO(this);
		}

		void VBO::Bind() const
		{
			m_Graphics->gl_bindVBO(this);
		}

		void VBO::Unbind() const
		{
			m_Graphics->gl_unbindVBO(this);
		}
	}
}

