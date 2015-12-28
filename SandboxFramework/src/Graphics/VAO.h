#pragma once

#include "../Collections/Dictionary.h"
#include "GraphicsDevice.h"
#include "VBOLocation.h"
#include "GLType.h"

namespace Sand {
	namespace Graphics {
		class VBO;

		class VAO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			unsigned int m_ID;

			Collections::Dictionary<VBO*, Collections::ArrayList<VBOLocation>*>* m_VBOLocations;
		public:
			VAO(GraphicsDevice* graphics);
			~VAO();

			void BindVBOToLocation(VBO* vbo, int location, int componentCount, GLType componentType = GLType::Float, int stride = 0, const void* offset = (const void*)0);

			void Bind() const;
			void Unbind() const;
		};
	}
}