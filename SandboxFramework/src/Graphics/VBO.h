#pragma once

#include "GraphicsDevice.h"

namespace SandboxFramework {
	namespace Graphics {
		class VBO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			GLuint m_ID;
			GLsizei m_Count;
			GLsizei m_ComponentCount;
		public:
			VBO(GraphicsDevice* graphics, GLfloat* vertices, GLsizei count, GLsizei componentCount);
			VBO(GraphicsDevice* graphics, GLsizei maxVertices, GLsizei componentCount);
			~VBO();

			GLvoid* Map();
			void Unmap();

			void Bind() const;
			void Unbind() const;
		};
	}
}