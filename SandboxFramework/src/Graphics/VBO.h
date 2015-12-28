#pragma once

#include "GraphicsDevice.h"

namespace Sand {
	namespace Graphics {
		class VBO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			unsigned int m_ID;
			int m_Count;
		public:
			VBO(GraphicsDevice* graphics, void* vertices, int vertexSize, int count);
			VBO(GraphicsDevice* graphics, int maxVertices, int vertexSize);
			~VBO();

			void* Map();
			void Unmap();

			void Bind() const;
			void Unbind() const;
		};
	}
}