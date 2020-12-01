#include "pch.h"
#include "FileReader.h"
#include <fstream>

namespace as3d::utility
{
	std::string ReadTextFile(const char* filePath)
	{
		std::ifstream file(filePath, std::ios::in | std::ios::ate);
		if (!file)
		{
			std::cerr << "Could not find file: " << filePath << '\n';
			return std::string();
		}
		// Check the size of the file
		size_t size = static_cast<size_t>(file.tellg());
		std::string content(size, '\0');
		// Return to the start and read the file
		file.seekg(0);
		file.read(content.data(), size);
		file.close();

		return content;
	}
}