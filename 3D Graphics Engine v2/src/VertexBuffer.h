#pragma once
#include <cstdint>

namespace as3d
{
	class VertexBuffer
	{
		uint32_t handle;
	public:
		VertexBuffer(const float* data, const size_t size);
		~VertexBuffer();
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		void Bind() const;
		void Unbind() const;
	};
}