// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_renderer_api.hpp"

namespace real {
	void gl_api::clear_color(glm::fvec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void gl_api::clear(int32_t bits) {
		glClear(bits);
	}

	void gl_api::draw_indexed(const real::reference<vertex_array> &vao) {
		vao->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // TODO: remove poly mode
		// glEnable(GL_DEPTH_TEST);
		// TODO: remove hardcoded mode
		glDrawElements(GL_TRIANGLES, vao->count(), GL_UNSIGNED_INT, nullptr);
	}

	renderer_api::api gl_api::enumval() const {
		return api::gl;
	}

	int32_t gl_api::default_clear_bits() const noexcept {
		return (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
