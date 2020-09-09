// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_RENDERER_BASE
#define VN_RENDERER_BASE

#include "version/core.hpp"
#include "version/renderer/renderer_api.hpp"

namespace vn {
	class VN_API renderer {
	public:
		[[nodiscard]] static inline renderer_api& api() noexcept { return *api_; }

		static void start_scene() noexcept;
		static void end_scene() noexcept;
		static void submit(const std::shared_ptr<vertex_array> &vao) noexcept;
	private:
		static renderer_api* api_;
	};
}

#endif //VN_RENDERER_BASE
