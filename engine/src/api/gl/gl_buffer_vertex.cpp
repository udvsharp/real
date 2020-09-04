// Copyright (c) 2020 udv. All rights reserved.

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "version/api/gl/gl_buffer_vertex.hpp"

namespace vn {

	gl_vertex_buffer::gl_vertex_buffer(float *data, unsigned int size)
			: layout_{}, vertex_array_{nullptr} {
		glGenBuffers(1, &renderer_id_);
		// TODO: remove hardcoded usage
		glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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

	void gl_vertex_buffer::set_layout(std::initializer_list<vertex_attribute> attributes) {
		layout_ = buffer_layout{attributes};
	}

	void gl_vertex_buffer::link_to(const std::shared_ptr<vn::vertex_array> &vertex_array) {
		vertex_array_ = vertex_array;
	}
}
