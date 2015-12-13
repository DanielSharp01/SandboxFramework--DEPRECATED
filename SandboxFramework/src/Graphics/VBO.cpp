#include "VBO.h"

#include "GraphicsDevice.h"

namespace SandboxFramework {
	namespace Graphics {

		VBO::VBO(GraphicsDevice* graphics, GLvoid* vertices, GLsizei vertexSize, GLsizei count)
			: m_Graphics(graphics), m_Count(count)
		{
			m_ID = m_Graphics->gl_createVBO(vertices, vertexSize * count);
		}

		VBO::VBO(GraphicsDevice* graphics, GLsizei maxVertices, GLsizei vertexSize)
			: m_Graphics(graphics), m_Count(maxVertices)
		{
			m_ID = m_Graphics->gl_createVBO(maxVertices * vertexSize);
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

