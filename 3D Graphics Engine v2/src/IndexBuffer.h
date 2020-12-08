#pragma once
#include <cstdint>

namespace as3d
{
	// For now, we'll only support 32 bit indices

	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* data, const size_t size);
		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		void Bind() const;
		void Unbind() const;

		// glDrawElements takes a signed int as the count for whatever reason, so we are going to give it what it wants
		int GetCount() const;
		unsigned int GetType() const;

	private:
		uint32_t handle;
		int count;
	};
}