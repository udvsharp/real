// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/array_vertex.hpp"
#include "real/api/gl/gl_array_vertex.hpp"

namespace Real
{
	Real::Scope<VertexArray> VertexArray::Make()
	{

		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return Real::MakeScope<GLVertexArray>();

		default:
		case RendererAPI::API::None:
			REAL_CORE_ERROR("Invalid renderer api: {}",
					static_cast<int32_t>(RendererAPI::API::None));
			return nullptr;
		}
	}

	VertexArray::~VertexArray() = default;
}
