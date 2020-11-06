// Copyright (c) 2020 udv. All rights reserved.

#include "real/renderer/buffer_layout.hpp"

namespace Real
{
	BufferLayout::BufferLayout(std::initializer_list<VertexAttribute> attributes)
			:attributes { attributes }
	{
		CalculateParams();
	}

	BufferLayout::BufferLayout()
			:attributes {}
	{

	}

	void BufferLayout::CalculateParams()
	{
		uint32_t offset = 0;

		for (auto& a : attributes)
		{
			a.offset = offset;
			offset += a.size;

			stride += a.size;
		}
	}
}
