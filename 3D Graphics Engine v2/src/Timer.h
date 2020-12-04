#pragma once

#include <chrono>

namespace as3d
{
	// A simple timer to measure the time between frames
	class Timer
	{
	public:
		Timer();
		float GetTime();

	private:
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start;
	};
}
