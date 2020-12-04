#include "pch.h"
#include "Timer.h"

namespace as3d
{
	Timer::Timer()
	{
		start = clock.now();
	}

	float Timer::GetTime()
	{
		std::chrono::duration<float, std::milli> duration = clock.now() - start;
		return duration.count();
	}
}