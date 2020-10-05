// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_INDEX
#define REAL_GL_BUFFER_INDEX

#include "real/core.hpp"
#include "real/renderer/buffer_index.hpp"

namespace real {
	class REAL_API gl_index_buffer : public index_buffer {
	private:
		renderer_id_t renderer_id_;
		uint32_t count_;
	public:
		gl_index_buffer(uint32_t* data, uint32_t size);
		~gl_index_buffer() override;

		void bind() const override;
		void unbind() const override;

		[[nodiscard]] uint32_t count() const override;
	};
}

#endif //REAL_GL_BUFFER_INDEX
