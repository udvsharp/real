// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_RENDERER_API
#define VN_GL_RENDERER_API

#include "version/core.hpp"
#include "version/renderer/renderer_api.hpp"
#include "version/renderer/array_vertex.hpp"

namespace vn {
	class VN_API gl_api : public renderer_api {
	public:
		virtual void clear_color(float r, float g, float b, float a) override;
		virtual void clear() override;
		virtual void draw_indexed(const std::shared_ptr<vertex_array> &vao) override;
		virtual api enumval() const override;
	};
}

#endif //VN_GL_RENDERER_API
