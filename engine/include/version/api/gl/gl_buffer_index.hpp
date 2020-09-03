// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_BUFFER_INDEX
#define VN_GL_BUFFER_INDEX

#include "version/core.hpp"
#include "version/renderer/buffer_index.hpp"

namespace vn {
	class VN_API gl_index_buffer : public index_buffer {
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

#endif //VN_GL_BUFFER_INDEX
