#include "pch.h"
#include "Gldebug.h"

namespace as3d
{
	namespace
	{
		void DebugCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
		{
			std::string sSource;
			std::string sType;
			std::string sSeverity;

			switch (source)
			{
			case GL_DEBUG_SOURCE_API:
				sSource = "OpenGL API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				sSource = "Window system"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				sSource = "Shader compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				sSource = "Third party"; break;
			case GL_DEBUG_SOURCE_APPLICATION:
				sSource = "Application"; break;
			default:
				sSource = "Unknown";
			}

			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR:
				sType = "Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				sType = "Deprecated behavior"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				sType = "Undefined behavior"; break;
			case GL_DEBUG_TYPE_PORTABILITY:
				sType = "Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				sType = "Performance issue"; break;
			default:
				sType = "Other";
			}

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				sSeverity = "HIGH"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				sSeverity = "MEDIUM"; break;
			case GL_DEBUG_SEVERITY_LOW:
				sSeverity = "LOW"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				sSeverity = "NOTIFICATION";
			}

			std::cerr << "GL error:\n"
				<< "source:\t\t" << sSource << '\n'
				<< "type:\t\t" << sType << '\n'
				<< "severity:\t" << sSeverity << '\n'
				<< message << '\n';

#ifdef _DEBUG
			__debugbreak();
#endif
		}
	}

	void InitDebug()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugCallback, nullptr);
	}
}