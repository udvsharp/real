// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERER_BASE
#define REAL_RENDERER_BASE

#include "real/transform.hpp"
#include "real/core.hpp"
#include "real/renderer/renderer_api.hpp"
#include "real/renderer/camera.hpp"
#include "real/renderer/base_shader.hpp"

namespace real {
	class REAL_API renderer {
	public:
		[[nodiscard]] static inline renderer_api& api() noexcept { return *api_; }

		static void start_scene(camera &camera) noexcept;
		static void end_scene() noexcept;
		static void submit(const real::reference<vertex_array> &vao, const real::reference<shader> &shader,
		                   const real::transform &model) noexcept;
	private:
		static renderer_api* api_;

		// TODO: remove this COMPLETELY Temporary stuff
		struct scene_data {
			glm::mat4 viewprojection;
		};

		static scene_data* data_;
	};
}

#endif //REAL_RENDERER_BASE
