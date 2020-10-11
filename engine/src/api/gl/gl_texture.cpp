// Copyright (c) 2020 udv. All rights reserved.

#include <stb/image.h>

#include "real/logger.hpp"
#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_texture.hpp"

namespace real {
	// region GL Texture2D
	gl_texture2d::gl_texture2d(const std::string &path)
			: path_{ path }, width_ {0}, height_ {0}, id_ {0} {}

	void gl_texture2d::init() {
		int w, h, channels;
		stbi_uc *data = stbi_load(path_.c_str(), &w, &h, &channels, 0);
		real_assert(data, "Failed to load texture image!");
		width_ = w;
		height_ = h;

		glCreateTextures(GL_TEXTURE_2D, 1, &id_);
		REAL_CORE_TRACE("LOL");
		glTextureStorage2D(id_, 1, GL_RGB8, width_, height_);

		glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(
				id_, 0,
				0, 0, width_, height_,
				channels == 3 ? GL_RGB : GL_RGBA,
				GL_UNSIGNED_BYTE, data
		);

		stbi_image_free(data);
	}

	gl_texture2d::~gl_texture2d() {
		glDeleteTextures(1, &id_);
	}

	void gl_texture2d::bind(uint32_t slot) const {
		glBindTextureUnit(slot, id_);
	}
	// endregion
}
