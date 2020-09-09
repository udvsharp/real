// Copyright (c) 2020 udv. All rights reserved.

#include "version/renderer/base_renderer.hpp"
#include "version/renderer/render_command.hpp"
#include "version/api/gl/gl_renderer_api.hpp"

namespace vn {
	// TODO: initialize dynamically
	renderer_api* renderer::api_ = new gl_api{};

	void renderer::start_scene() noexcept {

	}

	void renderer::end_scene() noexcept {

	}

	void renderer::submit(const std::shared_ptr<vertex_array> &vao) noexcept {
		// TODO: implement render command queue
		render_command::draw_indexed(vao);

	}
}
