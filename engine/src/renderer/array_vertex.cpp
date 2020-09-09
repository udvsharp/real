// Copyright (c) 2020 udv. All rights reserved.

#include "version/logger.hpp"
#include "version/renderer/base_renderer.hpp"
#include "version/renderer/array_vertex.hpp"
#include "version/api/gl/gl_array_vertex.hpp"

namespace vn {
	vertex_array *vertex_array::make() {

		switch (renderer::api().enumval()) {
			case renderer_api::api::gl:
				return new gl_vertex_array();

			default:
			case renderer_api::api::none:
				VN_CORE_ERROR("Invalid renderer api: {}", renderer_api::api::none);
				return nullptr;
		}
	}

	vertex_array::~vertex_array() {

	}
}
