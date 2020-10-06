// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDER_COMMAND
#define REAL_RENDER_COMMAND

#include <memory>

#include "real/core.hpp"
#include "real/renderer/array_vertex.hpp"

namespace real {
	class REAL_API render_command {
	public:
		static inline void clear_color(glm::fvec4 color) {
			renderer::api().clear_color(color);
		}

		static inline void clear() {
			renderer::api().clear();
		}

		static inline void draw_indexed(const real::reference<vertex_array> &vertex_array) {
			renderer::api().draw_indexed(vertex_array);
		}
	};
}

#endif //REAL_RENDER_COMMAND
