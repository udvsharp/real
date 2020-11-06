// Copyright (c) 2020 udv. All rights reserved.

#include <stb/image.h>

#include "real/logger.hpp"
#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_texture.hpp"

namespace Real
{
	// region GL Texture2D
	GLTexture2D::GLTexture2D(const std::string& path)
			:path { path }, width { 0 }, height { 0 }, rendererId { 0 }
	{}

	void GLTexture2D::Init()
	{
		int w, h, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
		real_msg_assert(data, "Failed to load texture image!");
		width = w;
		height = h;

		GLenum format_internal = 0, format_data = 0;
		if (channels == 4)
		{
			format_internal = GL_RGBA8;
			format_data = GL_RGBA;
		}
		else if (channels == 3)
		{
			format_internal = GL_RGB8;
			format_data = GL_RGB;
		}

		real_msg_assert(format_internal & format_data, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glTextureStorage2D(rendererId, 1, format_internal, width, height);
		glBindTexture(GL_TEXTURE_2D, rendererId);

		// TODO: add API support for parameters
		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(
				rendererId, 0,
				0, 0, width, height,
				format_data,
				GL_UNSIGNED_BYTE, data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &rendererId);
	}

	void GLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererId);
	}
	// endregion
}
