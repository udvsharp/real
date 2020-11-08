// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERING_CONTEXT_BASE
#define REAL_RENDERING_CONTEXT_BASE

#include "real/core.hpp"
#include "real/renderer/renderer_api.hpp"

namespace Real {
	class REAL_API RenderingContext {
	public:
		virtual ~RenderingContext();

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void VSync(bool enabled) = 0;
	};
}

#endif //REAL_RENDERING_CONTEXT_BASE
