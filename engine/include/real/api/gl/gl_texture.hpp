// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_TEXTURE
#define REAL_GL_TEXTURE

#include "real/core.hpp"
#include "real/renderer/base_texture.hpp"

namespace real {

	class REAL_API gl_texture2d : public real::texture2d {
	public:
		gl_texture2d(const std::string& path);
		~gl_texture2d();

		virtual void init() override;

		virtual inline texture_dimension_t width() const override { return width_; };
		virtual inline texture_dimension_t height() const override { return height_; };

		virtual void bind(uint32_t slot = 0) const override;
	private:
		std::string path_;

		texture_dimension_t width_;
		texture_dimension_t height_;

		renderer_id_t id_;
	};
}

#endif //REAL_GL_TEXTURE
