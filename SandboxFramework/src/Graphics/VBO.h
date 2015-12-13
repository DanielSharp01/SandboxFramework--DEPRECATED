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
		public:
			VBO(GraphicsDevice* graphics, GLvoid* vertices, GLsizei vertexSize, GLsizei count);
			VBO(GraphicsDevice* graphics, GLsizei maxVertices, GLsizei vertexSize);
			~VBO();

			GLvoid* Map();
			void Unmap();

			void Bind() const;
			void Unbind() const;
		};
	}
}