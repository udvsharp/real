// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_INDEX
#define REAL_GL_BUFFER_INDEX

#include "real/core.hpp"
#include "real/renderer/buffer_index.hpp"

namespace real {
	class REAL_API gl_index_buffer : public index_buffer {
	private:
		renderer_id_t renderer_id_;
		unsigned int count_;
	public:
		gl_index_buffer(unsigned int* data, unsigned int size);
		virtual ~gl_index_buffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual unsigned int count() const override;
	};
}

#endif //REAL_GL_BUFFER_INDEX
