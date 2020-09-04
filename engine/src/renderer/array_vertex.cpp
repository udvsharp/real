// Copyright (c) 2020 udv. All rights reserved.

#include "version/renderer/array_vertex.hpp"
#include "version/api/gl/gl_array_vertex.hpp"

namespace vn {
	vertex_array *vertex_array::make() {

		switch (renderer::api()) {
			case renderer::renderer_api::GL:
				return new gl_vertex_array();

			default:
			case renderer::renderer_api::none:
				VN_CORE_ERROR("Invalid renderer api: {}", renderer::renderer_api::none);
				return nullptr;
		}
	}

	vertex_array::~vertex_array() {

	}
}
