// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_RENDERER_API
#define REAL_GL_RENDERER_API

#include "real/core.hpp"
#include "real/renderer/renderer_api.hpp"
#include "real/renderer/array_vertex.hpp"

namespace real {
	class REAL_API gl_api : public renderer_api {
	public:
		virtual void clear_color(glm::fvec4 color) override;
		virtual void clear(int32_t bits) override;
		virtual void draw_indexed(const std::shared_ptr<vertex_array> &vao) override;
		virtual api enumval() const override;
	private:
		virtual int32_t default_clear_bits() const noexcept override;
	};
}

#endif //REAL_GL_RENDERER_API
