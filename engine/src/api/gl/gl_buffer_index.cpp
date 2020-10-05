// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace real {

	gl_index_buffer::gl_index_buffer(unsigned int *data, unsigned int size)
			: count_{size} {
		glGenBuffers(1, &renderer_id_);
		// TODO: remove hardcoded buffer data usage
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
	}

	gl_index_buffer::~gl_index_buffer() {
		glDeleteBuffers(1, &renderer_id_);
	}

	void gl_index_buffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
	}

	void gl_index_buffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	unsigned int gl_index_buffer::count() const {
		return count_;
	}
}
