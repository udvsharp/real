// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERING_CONTEXT_BASE
#define REAL_RENDERING_CONTEXT_BASE

#include "real/core.hpp"

namespace Real {
	class REAL_API RenderingContext {
		// TODO: extend supported rendering api list
		enum class api : char {
			none = -1,
			GL = 0,
		};
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void VSync(bool enabled) = 0;

		static RenderingContext *make(api api);
	};
}

#endif //REAL_RENDERING_CONTEXT_BASE
