#pragma once
#include <cstdint>
#include "VertexBuffer.h"

namespace as3d
{
	struct LayoutElement
	{
		uint32_t type;
		uint32_t count;

		static uint32_t GetSizeOf(uint32_t type);
	};

	struct BufferLayout
	{
		std::vector<LayoutElement> elements;
		uint32_t stride = 0;

		template<typename T>
		void Push(uint32_t count);

		template<>
		void Push<int8_t>(uint32_t count);

		template<>
		void Push<uint8_t>(uint32_t count);

		template<>
		void Push<int16_t>(uint32_t count);

		template<>
		void Push<uint16_t>(uint32_t count);

		template<>
		void Push<int32_t>(uint32_t count);

		template<>
		void Push<uint32_t>(uint32_t count);
		
		template<>
		void Push<float>(uint32_t count);

		template<>
		void Push<double>(uint32_t count);
	};

	class VertexArray
	{
		uint32_t handle;
		uint32_t nextIndex;

	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);
	};
}