// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_VERTEX_BUFFER
#define VN_VERTEX_BUFFER

#include "version/core.hpp"
#include "version/renderer/base_rendering_context.hpp"
#include "version/renderer/buffer_layout.hpp"

namespace vn {
	class VN_API vertex_buffer {
	private:
	public:
		virtual ~vertex_buffer();

		[[nodiscard]] virtual const buffer_layout& layout() const = 0;
		virtual void set_layout(std::initializer_list<vertex_attribute> attributes) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	public:
		static vertex_buffer *make(float* data, unsigned int size);
	};
}

#endif //VN_VERTEX_BUFFER
