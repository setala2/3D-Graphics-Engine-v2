#include "pch.h"
#include "KeyEvent.h"

namespace as3d
{
	KeyEvent::KeyEvent(Keycode key, Action action)
		: key(key), action(action)
	{	}

	std::string KeyEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Key event:\n" << "Keycode: " << AsInt(key) << '\n' <<
			"Action " << AsInt(action);
		return ss.str();
	}

	CharEvent::CharEvent(uint32_t codePoint)
		:codePoint(codePoint)
	{	}

	std::string CharEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Char event: " << codePoint;
		return ss.str();
	}
}