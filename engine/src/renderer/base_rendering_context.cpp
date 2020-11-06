// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer.hpp"

namespace Real
{
	// FIXME: write make rendering context method if needed
	RenderingContext* RenderingContext::make(api api)
	{
		switch (api)
		{
		case api::GL:
			return nullptr;
			// return new gl_rendering_context{};

		default:
		case api::none:
			REAL_CORE_ERROR("Invalid api: {}", api);
			return nullptr;
		}
	}
}
