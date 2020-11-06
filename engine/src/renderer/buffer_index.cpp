// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace Real
{

	IndexBuffer* IndexBuffer::Make(uint32_t* data, uint32_t size)
	{

		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return new GLIndexBuffer(data, size);

		default:
		case RendererAPI::API::none:
			REAL_CORE_ERROR("Invalid renderer api: {}",
					RendererAPI::API::none);
			return nullptr;
		}
	}

	IndexBuffer::~IndexBuffer() = default;

}
