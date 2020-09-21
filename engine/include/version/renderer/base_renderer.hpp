// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_RENDERER_BASE
#define VN_RENDERER_BASE

#include "version/core.hpp"
#include "version/renderer/renderer_api.hpp"
#include "version/renderer/camera.hpp"
#include "version/renderer/shader.hpp"

namespace vn {
	class VN_API renderer {
	public:
		[[nodiscard]] static inline renderer_api& api() noexcept { return *api_; }

		static void start_scene(vn::camera_orthographic &camera) noexcept;
		static void end_scene() noexcept;
		static void submit(const std::shared_ptr<vertex_array> &vao, const std::shared_ptr<vn::shader> &shader) noexcept;
	private:
		static renderer_api* api_;

		// TODO: remove this COMPLETELY Temporary stuff
		struct scene_data {
			glm::mat4 viewprojection;
		};

		static scene_data* data_;
	};
}

#endif //VN_RENDERER_BASE
