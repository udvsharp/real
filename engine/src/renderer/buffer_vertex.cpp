// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/buffer_vertex.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"
#include "real/renderer/renderer_api.hpp"

namespace real {

	vertex_buffer *vertex_buffer::make(float *data, uint32_t size) {
		switch (renderer::api().enumval()) {
			case renderer_api::api::gl: return new gl_vertex_buffer(data, size);

			default:
			case renderer_api::api::none: REAL_CORE_ERROR("Invalid renderer api: {}",
			                                              renderer_api::api::none);
				return nullptr;
		}

	}

	vertex_buffer::~vertex_buffer() = default;

}
