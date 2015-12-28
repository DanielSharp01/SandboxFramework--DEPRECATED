#pragma once

#include "GraphicsDevice.h"

namespace Sand {
	namespace Graphics {
		class IBO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			unsigned int m_ID;
			int m_Count;
		public:
			IBO(GraphicsDevice* graphics, GLushort* indices, int count);
			~IBO();

			void Bind() const;
			void Unbind() const;
		};
	}
}