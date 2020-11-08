// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/buffer_vertex.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"
#include "real/renderer/renderer_api.hpp"

namespace Real
{

	VertexBuffer* VertexBuffer::Make(float* data, uint32_t size)
	{
		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return new GLVertexBuffer(data, size);

		default:
		case RendererAPI::API::None:
			REAL_CORE_ERROR("Invalid renderer api: {}",
					RendererAPI::API::None);
			return nullptr;
		}

	}

	VertexBuffer::~VertexBuffer() = default;

}
