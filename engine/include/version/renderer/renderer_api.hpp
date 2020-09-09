// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_RENDERER_API
#define VN_RENDERER_API

#include <memory>

#include "version/core.hpp"

namespace vn {
	class vertex_array;

	class VN_API renderer_api {
	public:
		enum class api {
			none = 0,
			gl = 1,
		};
	public:
		virtual void clear_color(float r, float g, float b, float a) = 0;
		virtual void clear() = 0;

		virtual api enumval() const = 0;

		virtual void draw_indexed(const std::shared_ptr<vertex_array>& vao) = 0;
	private:
		// static api api_;
	};
}

#endif //VN_RENDERER_API
