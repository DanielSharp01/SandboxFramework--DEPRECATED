#include "IBO.h"

#include <iostream> //TODO: DELETE + ALSO COUT
#include "GraphicsDevice.h"

namespace Sand {
	namespace Graphics {
		IBO::IBO(GraphicsDevice* graphics, GLushort* indices, GLsizei count)
			: m_Graphics(graphics), m_Count(count)
		{
			m_ID = m_Graphics->gl_createIBO(indices, m_Count);
		}

		IBO::~IBO()
		{
			m_Graphics->gl_destroyIBO(this);
		}

		void IBO::Bind() const
		{
			m_Graphics->gl_bindIBO(this);
		}

		void IBO::Unbind() const
		{
			m_Graphics->gl_unbindIBO(this);
		}
	}
}

