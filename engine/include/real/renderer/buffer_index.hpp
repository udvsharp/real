// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_INDEX_BUFFER
#define REAL_INDEX_BUFFER

#include "real/core.hpp"

namespace Real {
	class REAL_API IndexBuffer {
	private:
	public:
		virtual ~IndexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual uint32_t Count() const = 0;
	public:
		static Real::Scope<IndexBuffer> Make(uint32_t *data, uint32_t size);
	};
}

#endif //REAL_INDEX_BUFFER
