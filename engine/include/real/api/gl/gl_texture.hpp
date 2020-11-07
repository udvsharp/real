// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_TEXTURE
#define REAL_GL_TEXTURE

#include "real/core.hpp"
#include "real/renderer/base_texture.hpp"

namespace Real
{

	class REAL_API GLTexture2D : public Real::Texture2D
	{
	public:
		GLTexture2D(const std::string& path);
		~GLTexture2D();

		virtual void Init() override;

		virtual texture_dimension_t Width() const override
		{ return width; };
		virtual texture_dimension_t Height() const override
		{ return height; };

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string path;

		texture_dimension_t width;
		texture_dimension_t height;

		renderer_id_t rendererId;
	};
}

#endif //REAL_GL_TEXTURE
