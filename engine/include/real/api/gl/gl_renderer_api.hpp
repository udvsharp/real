// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_RENDERER_API
#define REAL_GL_RENDERER_API

#include "real/core.hpp"
#include "real/renderer/renderer_api.hpp"
#include "real/renderer/array_vertex.hpp"

namespace Real
{
	class REAL_API GLRendererApi : public RendererAPI
	{
	public:
		virtual void Init() override;
		void ClearColor(glm::fvec4 color) override;
		void Clear(int32_t bits) override;
		void DrawIndexed(const Real::Reference<VertexArray>& vao) override;
		[[nodiscard]] API Value() const override;
	private:
		[[nodiscard]] int32_t DefaultClearBits() const noexcept override;
	};
}

#endif //REAL_GL_RENDERER_API
