// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_VERTEX_BUFFER
#define REAL_VERTEX_BUFFER

#include <memory>

#include "real/core.hpp"
#include "real/renderer/base_rendering_context.hpp"
#include "real/renderer/buffer_layout.hpp"

namespace Real {
	class VertexArray;

	class REAL_API VertexBuffer {
	public:
		virtual ~VertexBuffer();

		[[nodiscard]] virtual const BufferLayout &Layout() const = 0;

		virtual void Layout(std::initializer_list<VertexAttribute> attributes) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		static Real::Scope<VertexBuffer> Make(float *data, uint32_t size);
	};
}

#endif //REAL_VERTEX_BUFFER
