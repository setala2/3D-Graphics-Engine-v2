#pragma once

namespace as3d::utility
{
	struct Image
	{
		Image(const char* path);
		~Image();

		int width = 0, height = 0, channels = 0;
		unsigned char* data = nullptr;
	};
}