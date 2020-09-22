// Copyright (c) 2020 udv. All rights reserved.

#include "version/api/gl/gl_headers.hpp"
#include "version/api/gl/gl_renderer_api.hpp"

namespace vn {
	void gl_api::clear_color(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void gl_api::clear() {
		// TODO: remove hardcoded bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void gl_api::draw_indexed(const std::shared_ptr<vertex_array> &vao) {
		// TODO: remove hardcoded mode
		vao->bind();

		// remove this tesiting
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, vao->count(), GL_UNSIGNED_INT, nullptr);
	}

	renderer_api::api gl_api::enumval() const {
		return api::gl;
	}
}
