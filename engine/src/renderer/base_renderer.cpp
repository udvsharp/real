// Copyright (c) 2020 udv. All rights reserved.

#include <version/renderer/camera.hpp>
#include "version/renderer/base_renderer.hpp"
#include "version/renderer/render_command.hpp"
#include "version/api/gl/gl_renderer_api.hpp"

namespace vn {
	// TODO: initialize dynamically
	renderer_api* renderer::api_ = new gl_api{};
	renderer::scene_data* renderer::data_ = new renderer::scene_data{};

	void renderer::start_scene(camera &camera) noexcept {
		data_->viewprojection = camera.viewprojection();
	}

	void renderer::end_scene() noexcept {

	}

	void renderer::submit(const std::shared_ptr<vertex_array> &vao, const std::shared_ptr<shader> &shader) noexcept {
		shader->bind();
		shader->uniform("u_vp", data_->viewprojection);
		// TODO: implement render command queue
		render_command::draw_indexed(vao);

	}
}
