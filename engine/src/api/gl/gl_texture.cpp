// Copyright (c) 2020 udv. All rights reserved.

#include <stb/image.h>

#include "real/logger.hpp"
#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_texture.hpp"

namespace real {
	// region GL Texture2D
	gl_texture2d::gl_texture2d(const std::string &path)
			: path_{ path }, width_{ 0 }, height_{ 0 }, id_{ 0 } {}

	void gl_texture2d::init() {
		int w, h, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc *data = stbi_load(path_.c_str(), &w, &h, &channels, 0);
		real_msg_assert(data, "Failed to load texture image!");
		width_ = w;
		height_ = h;

		GLenum format_internal = 0, format_data = 0;
		if (channels == 4) {
			format_internal = GL_RGBA8;
			format_data = GL_RGBA;
		} else if (channels == 3) {
			format_internal = GL_RGB8;
			format_data = GL_RGB;
		}

		real_msg_assert(format_internal & format_data, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &id_);
		glTextureStorage2D(id_, 1, format_internal, width_, height_);
		glBindTexture(GL_TEXTURE_2D, id_);

		// TODO: add API support for parameters
		glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(
				id_, 0,
				0, 0, width_, height_,
				format_data,
				GL_UNSIGNED_BYTE, data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

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
