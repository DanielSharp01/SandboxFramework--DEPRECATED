#pragma once

#include "GraphicsDevice.h"

namespace SandboxFramework {
	namespace Graphics {
		class IBO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			GLuint m_ID;
			GLsizei m_Count;
		public:
			IBO(GraphicsDevice* graphics, GLushort* indices, GLsizei count);
			~IBO();

			void Bind() const;
			void Unbind() const;
		};
	}
}