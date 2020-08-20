// Copyright (c) 2020 udv. All rights reserved.

#include "version/logger.hpp"
#include "version/renderer.hpp"

namespace vn {
	// FIXME: write make rendering context method if needed
	rendering_context *rendering_context::make(api api) {
		switch (api) {
			case api::GL: {
				return nullptr;
				// return new gl_rendering_context{};
			}

			case api::none:
			default: {
				VN_CORE_ERROR("Invalid api: {}", api);
				return nullptr;
			}
		}
	}
}
