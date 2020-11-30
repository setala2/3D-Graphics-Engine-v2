#include "pch.h"
#include "Event.h"

namespace as3d
{
	std::ostream& operator<<(std::ostream& stream, const Event& event)
	{
		stream << event.ToString();
		return stream;
	}
}