#include "pch.h"
#include "VertexArray.h"

namespace as3d
{
	// https://www.khronos.org/opengl/wiki/OpenGL_Type
	uint32_t LayoutElement::GetSizeOf(uint32_t type)
	{
		switch (type)
		{
		case GL_BYTE:			return 1;
		case GL_UNSIGNED_BYTE:	return 1;
		case GL_SHORT:			return 2;
		case GL_UNSIGNED_SHORT:	return 2;
		case GL_INT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_FLOAT:			return 4;
		case GL_DOUBLE:			return 8;
		}
		return 0;
	}

	template<typename T>
	void BufferLayout::Push(uint32_t count)
	{
		std::cout << "Trying to push an unknown type to a layout.\n";
	}

	template<>
	void BufferLayout::Push<int8_t>(uint32_t count)
	{
		elements.push_back({ GL_BYTE, count });
		stride += LayoutElement::GetSizeOf(GL_BYTE) * count;
	}

	template<>
	void BufferLayout::Push<uint8_t>(uint32_t count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count });
		stride += LayoutElement::GetSizeOf(GL_UNSIGNED_BYTE) * count;
	}
	
	template<>
	void BufferLayout::Push<int16_t>(uint32_t count)
	{
		elements.push_back({ GL_SHORT, count });
		stride += LayoutElement::GetSizeOf(GL_SHORT) * count;
	}

	template<>
	void BufferLayout::Push<uint16_t>(uint32_t count)
	{
		elements.push_back({ GL_UNSIGNED_SHORT, count });
		stride += LayoutElement::GetSizeOf(GL_UNSIGNED_SHORT) * count;
	}
	
	template<>
	void BufferLayout::Push<int32_t>(uint32_t count)
	{
		elements.push_back({ GL_INT, count });
		stride += LayoutElement::GetSizeOf(GL_INT) * count;
	}

	template<>
	void BufferLayout::Push<uint32_t>(uint32_t count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count });
		stride += LayoutElement::GetSizeOf(GL_UNSIGNED_INT) * count;
	}

	template<>
	void BufferLayout::Push<float>(uint32_t count)
	{
		elements.push_back({ GL_FLOAT, count });
		stride += LayoutElement::GetSizeOf(GL_FLOAT) * count;
	}

	template<>
	void BufferLayout::Push<double>(uint32_t count)
	{
		elements.push_back({ GL_DOUBLE, count });
		stride += LayoutElement::GetSizeOf(GL_DOUBLE) * count;
	}

	VertexArray::VertexArray()
		: nextIndex(0)
	{
		glGenVertexArrays(1, &handle);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &handle);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(handle);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
	{
		const auto& elements = layout.elements;
		std::size_t elementOffset = 0;

		Bind();
		vb.Bind();	// vb must be bound when we call glVertexAttribPointer

		for (; nextIndex < elements.size(); ++nextIndex)
		{
			LayoutElement currentElement = elements[nextIndex];
			glEnableVertexAttribArray(nextIndex);
			glVertexAttribPointer(nextIndex, currentElement.count, currentElement.type, GL_FALSE, layout.stride, (const void*)elementOffset);
			elementOffset += currentElement.count * static_cast<std::size_t>(LayoutElement::GetSizeOf(currentElement.type));
		}

		vb.Unbind();
		Unbind();
	}
}