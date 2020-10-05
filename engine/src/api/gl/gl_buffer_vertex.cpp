// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"

namespace real {

	gl_vertex_buffer::gl_vertex_buffer(float *data, unsigned int size)
			: layout_{}, vertex_array_{nullptr} {
		glGenBuffers(1, &renderer_id_);
		// TODO: remove hardcoded buffer data usage
		glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	gl_vertex_buffer::~gl_vertex_buffer() {
		glDeleteBuffers(1, &renderer_id_);
	}

	void gl_vertex_buffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
	}

	void gl_vertex_buffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void gl_vertex_buffer::layout(std::initializer_list<vertex_attribute> attributes) {
		layout_ = buffer_layout{attributes};
	}

	void gl_vertex_buffer::link_to(const std::shared_ptr<real::vertex_array> &vertex_array) {
		vertex_array_ = vertex_array;
	}
}
