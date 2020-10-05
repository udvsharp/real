// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/array_vertex.hpp"
#include "real/api/gl/gl_array_vertex.hpp"

namespace real {
	vertex_array *vertex_array::make() {

		switch (renderer::api().enumval()) {
			case renderer_api::api::gl:
				return new gl_vertex_array();

			default:
			case renderer_api::api::none:
				REAL_CORE_ERROR("Invalid renderer api: {}", renderer_api::api::none);
				return nullptr;
		}
	}

	vertex_array::~vertex_array() {

	}
}
