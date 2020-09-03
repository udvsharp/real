// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_BUFFER_VERTEX
#define VN_GL_BUFFER_VERTEX

#include "version/core.hpp"
#include "version/renderer/buffer_vertex.hpp"

namespace vn {
	class VN_API gl_vertex_buffer : public vertex_buffer {
	private:
		renderer_id_t renderer_id_;
	public:
		gl_vertex_buffer(float* data, unsigned int size);
		virtual ~gl_vertex_buffer();

		virtual void bind() const override;
		virtual void unbind() const override;
	};
}

#endif //VN_GL_BUFFER_VERTEX
