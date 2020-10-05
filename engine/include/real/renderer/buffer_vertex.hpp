// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_VERTEX_BUFFER
#define REAL_VERTEX_BUFFER

#include <memory>

#include "real/core.hpp"
#include "real/renderer/base_rendering_context.hpp"
#include "real/renderer/buffer_layout.hpp"

namespace real {
	class vertex_array;

	class REAL_API vertex_buffer {
	private:
	public:
		virtual ~vertex_buffer();

		[[nodiscard]] virtual const buffer_layout& layout() const = 0;
		[[nodiscard]] virtual const std::shared_ptr<real::vertex_array> & vertex_array() const = 0;

		virtual void layout(std::initializer_list<vertex_attribute> attributes) = 0;
		virtual void link_to(const std::shared_ptr<real::vertex_array> &vertex_array) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	public:
		static vertex_buffer *make(float* data, uint32_t size);
	};
}

#endif //REAL_VERTEX_BUFFER
