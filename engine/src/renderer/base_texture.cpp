// Copyright (c) 2020 udv. All rights reserved.

#include "real/renderer/base_texture.hpp"

#include <memory>

#include "real/renderer.hpp"

namespace real {

	// region Texture
	texture::~texture() = default;
	// endregion Texture
	// region Texture2D
	real::reference<texture2d> texture2d::make(const std::string& path) {
		switch (renderer::api().enumval()) {
			case renderer_api::api::gl: return std::make_shared<gl_texture2d>(path);

			default:
			case renderer_api::api::none:
				REAL_CORE_ERROR("Invalid renderer api: {}", renderer_api::api::none);
				return nullptr;
		}
	}

	texture2d::~texture2d() = default;
	// endregion Texture2d
}
