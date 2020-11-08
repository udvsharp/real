// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERER_API
#define REAL_RENDERER_API

#include <memory>
#include <glm/fwd.hpp>

#include "real/core.hpp"

namespace Real {
	class VertexArray;

	class REAL_API RendererAPI {
	public:
		enum class API {
			None = 0,
			GL = 1,
		};
	public:
		virtual void Init() = 0;
		virtual void ClearColor(glm::fvec4 color) = 0;
		void clear() { Clear(DefaultClearBits()); };
		virtual void Clear(int32_t bits) = 0;

		[[nodiscard]] virtual API Value() const = 0;

		virtual void DrawIndexed(const Real::Reference<VertexArray> &vao) = 0;
	private:
		[[nodiscard]] virtual constexpr int32_t DefaultClearBits() const noexcept = 0;
		// static api api_;
	};
}

#endif //REAL_RENDERER_API
