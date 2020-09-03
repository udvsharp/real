// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_INDEX_BUFFER
#define VN_INDEX_BUFFER

#include "version/core.hpp"
#include "version/renderer/base_rendering_context.hpp"

namespace vn {
	class VN_API index_buffer {
	private:
	public:
		virtual ~index_buffer();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		[[nodiscard]] virtual unsigned int count() const = 0;
	public:
		static index_buffer *make(unsigned int* data, unsigned int size);
	};
}

#endif //VN_INDEX_BUFFER
