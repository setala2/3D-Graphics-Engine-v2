#include "pch.h"
#include "IndexBuffer.h"

namespace as3d
{
	IndexBuffer::IndexBuffer(const uint32_t* data, const size_t size)
		: count(size / sizeof(uint32_t))
	{
		glGenBuffers(1, &handle);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		Unbind();
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &handle);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::GetCount() const
	{
		return count;
	}

	uint32_t IndexBuffer::GetType() const
	{
		return GL_UNSIGNED_INT;
	}
}