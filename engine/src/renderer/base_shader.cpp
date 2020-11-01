// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>
#include <real/renderer/base_shader.hpp>

#include "real/logger.hpp"
#include "real/renderer.hpp"

namespace real {
	real::reference<shader> shader::make(std::string filename) {
		switch (renderer::api().enumval()) {
			case renderer_api::api::gl: return real::make_reference<gl_shader>(filename);

			default:
			case renderer_api::api::none: REAL_CORE_ERROR("Invalid renderer api: {}",
			                                              renderer_api::api::none);
				return nullptr;
		}
	}

	shader::~shader() = default;

	// Shader library
	void shader_lib::add(const real::reference<shader> &shader) {
		if (shaders_.contains(shader->name())) {
			return;
		}

		auto &name = shader->name();
		shaders_[name] = shader;
	}

	real::reference<shader> shader_lib::load(const std::string &filename) {
		auto shader = shader::make(filename);
		add(shader);
		return shader;
	}

	real::reference<shader>
	shader_lib::load(const std::string &name, const std::string &filename) {
		auto shader = shader::make(filename);
		shader->name(name);
		add(shader);
		return shader;
	}

	bool shader_lib::contains(const std::string &name) {
		return shaders_.contains(name);
	}

	real::reference<shader> shader_lib::get(const std::string &name) {
		real_msg_assert(contains(name), "Shader not found!"); // TODO: assertions
		return shaders_[name];
	}
}
