#include "pch.h"
#include "Image.h"
#include "stb_image/stb_image.h"

namespace as3d::utility
{
	Image::Image(const char* path)
	{
		data = stbi_load(path, &width, &height, &channels, 4);
		// Not going to enforce this succeeding, at least for now
		if (!data)
			std::cerr << "Could not load an image: " << path << '\n';
	}

	Image::~Image()
	{
		stbi_image_free(data);
	}

}