// Copyright (c) 2020 udv. All rights reserved.

#include "real/transform.hpp"
#include "real/renderer/camera.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/render_command.hpp"
#include "real/api/gl/gl_renderer_api.hpp"

namespace real {
	// TODO: initialize dynamically
	renderer_api* renderer::api_ = new gl_api{};
	renderer::scene_data* renderer::data_ = new renderer::scene_data{};

	void renderer::start_scene(real::camera &camera) noexcept {
		data_->viewprojection = camera.viewprojection();
	}

	void renderer::end_scene() noexcept {

	}

	void renderer::submit(const std::shared_ptr<vertex_array> &vao, const std::shared_ptr<shader> &shader,
	                      const real::transform &model) noexcept {
		shader->bind();
		shader->uniform_matrix("u_vp", data_->viewprojection);
		shader->uniform_matrix("u_model", model.matrix());
		shader->uniform_float("u_color", { 1.0f, 1.0f, 1.0f, 1.0f });
		// TODO: implement render command queue
		render_command::draw_indexed(vao);

	}
}
