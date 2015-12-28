#include "IndexOutOfBoundsException.h"

namespace Collections {
	IndexOutOfBoundsException::IndexOutOfBoundsException(int index)
		: m_Index(index)
	{ }

	std::string IndexOutOfBoundsException::Message() const
	{
		return "Runtime Exception: Index out of bounds " + std::to_string(m_Index);
	}
}