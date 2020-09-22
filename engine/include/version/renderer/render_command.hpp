// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_RENDER_COMMAND
#define VN_RENDER_COMMAND

#include <memory>

#include "version/core.hpp"
#include "version/renderer/array_vertex.hpp"

namespace vn {
	class VN_API render_command {
	public:
		static inline void clear_color(glm::fvec4 color) {
			renderer::api().clear_color(color);
		}

		static inline void clear() {
			renderer::api().clear();
		}

		static inline void draw_indexed(const std::shared_ptr<vertex_array> &vertex_array) {
			renderer::api().draw_indexed(vertex_array);
		}
	};
}

#endif //VN_RENDER_COMMAND
