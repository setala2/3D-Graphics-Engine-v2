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
}