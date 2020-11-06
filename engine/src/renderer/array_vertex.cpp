// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/array_vertex.hpp"
#include "real/api/gl/gl_array_vertex.hpp"

namespace Real
{
	VertexArray* VertexArray::Make()
	{

		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return new GLVertexArray();

		default:
		case RendererAPI::API::none:
			REAL_CORE_ERROR("Invalid renderer api: {}",
					RendererAPI::API::none);
			return nullptr;
		}
	}

	VertexArray::~VertexArray() = default;
}
