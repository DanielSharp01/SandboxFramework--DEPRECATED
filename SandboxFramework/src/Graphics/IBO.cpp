#include "IBO.h"
#include "GraphicsDevice.h"

namespace Sand {
	namespace Graphics {
		IBO::IBO(GraphicsDevice* graphics, GLushort* indices, int count)
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

