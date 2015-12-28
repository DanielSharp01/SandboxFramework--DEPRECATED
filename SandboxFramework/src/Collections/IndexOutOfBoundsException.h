#pragma once
#include "../Debug/Exception.h"

namespace Collections {
	class IndexOutOfBoundsException : public Debug::Exception
	{
	private:
		int m_Index;
	public:
		IndexOutOfBoundsException(int index);
		std::string Message() const override;
	};
}
