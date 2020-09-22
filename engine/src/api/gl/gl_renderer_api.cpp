// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>

#include "version/api/gl/gl_headers.hpp"
#include "version/api/gl/gl_renderer_api.hpp"

namespace vn {
	void gl_api::clear_color(glm::fvec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void gl_api::clear(int32_t bits) {
		glClear(bits);
	}

	void gl_api::draw_indexed(const std::shared_ptr<vertex_array> &vao) {
		// TODO: remove hardcoded mode
		vao->bind();
		glDrawElements(GL_TRIANGLES, vao->count(), GL_UNSIGNED_INT, nullptr);
	}

	renderer_api::api gl_api::enumval() const {
		return api::gl;
	}

	int32_t gl_api::default_clear_bits() const noexcept {
		return (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
