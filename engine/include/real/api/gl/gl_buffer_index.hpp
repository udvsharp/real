// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_INDEX
#define REAL_GL_BUFFER_INDEX

#include "real/core.hpp"
#include "real/renderer/buffer_index.hpp"

namespace Real {
	class REAL_API GLIndexBuffer : public IndexBuffer {
	public:
		GLIndexBuffer(uint32_t *data, uint32_t size);
		~GLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] uint32_t Count() const override;
	private:
		renderer_id_t rendererId;
		uint32_t count;
	};
}

#endif //REAL_GL_BUFFER_INDEX
