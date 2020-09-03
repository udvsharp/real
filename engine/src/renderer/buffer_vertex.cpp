// Copyright (c) 2020 udv. All rights reserved.

#include "version/logger.hpp"
#include "version/renderer/base_renderer.hpp"
#include "version/renderer/buffer_vertex.hpp"
#include "version/api/gl/gl_buffer_vertex.hpp"

namespace vn {

	vertex_buffer *vertex_buffer::make(float *data, unsigned int size) {
		switch (renderer::api()) {
			case renderer::renderer_api::GL:
				return new gl_vertex_buffer(data, size);

			default:
			case renderer::renderer_api::none:
				VN_CORE_ERROR("Invalid renderer api: {}", renderer::renderer_api::none);
				return nullptr;
		}

	}

	vertex_buffer::~vertex_buffer() {}

}
