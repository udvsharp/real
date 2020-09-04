// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_RENDERER_BASE
#define VN_RENDERER_BASE

#include "version/core.hpp"

namespace vn {
	class VN_API renderer {
	public:
		enum class renderer_api {
			none = 0,
			GL = 1,
		};
	public:
		[[nodiscard]] static inline renderer_api api() noexcept { return api_; }
	private:
		static renderer_api api_;
	};
}

#endif //VN_RENDERER_BASE
