// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>

#include "version/logger.hpp"
#include "version/renderer.hpp"

namespace vn {
	shader *shader::make() {
		switch (renderer::api().enumval()) {
			case renderer_api::api::gl: return new gl_shader{};

			default:
			case renderer_api::api::none:
				VN_CORE_ERROR("Invalid renderer api: {}", renderer_api::api::none);
				return nullptr;
		}
	}

	shader::~shader() {}
}
