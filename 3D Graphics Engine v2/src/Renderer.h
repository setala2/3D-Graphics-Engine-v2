#pragma once
#include <GL/glew.h>

namespace as3d
{
	// It's called 'Renderer' but it doesn't actually render anything, hmmmm...
	class Renderer
	{
		GLbitfield clearFlags;
		bool wireframe;
		bool bfc;
		bool depthTest;
		bool blend;

		const char* on = "on";
		const char* off = "off";

	public:
		Renderer();

		void Clear() const;

		void DrawControlWindow(const char* title);

		void SetClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) const;
		void EnableBackFaceCulling(bool enable);
		void EnableDepthTesting(bool enable, GLenum depthFunction = GL_LESS);
		void EnableWireFrame(bool enable);
		void ToggleWireFrame();
		void ToggleBackFaceCulling();
		void ToggleDepthTest();	// Can't change the depth function with this
		void EnableBlending(bool enable, GLenum src = GL_SRC_ALPHA, GLenum dest = GL_ONE_MINUS_SRC_ALPHA);
		void ToggleBlending();
		void SetViewPort(int32_t width, int32_t height);

	private:
		void SetFlag(GLbitfield flag, bool set);
	};
}
