// Copyright (c) 2020 udv. All rights reserved.

#include "version/api/gl/gl_headers.hpp"
#include "version/api/gl/gl_array_vertex.hpp"

namespace vn {
	gl_vertex_array::gl_vertex_array()
		: vertex_buffers_{}, index_buffers_{} {
		glGenVertexArrays(1, &renderer_id_);
	}

	gl_vertex_array::~gl_vertex_array() {
		glDeleteVertexArrays(1, &renderer_id_);
	}

	void gl_vertex_array::add_vertex_buffer(const std::shared_ptr<vn::vertex_buffer> &buffer) {
		vn_assert(buffer->layout().attributes().size(), "Vertex buffer has no layout!");

		glBindVertexArray(renderer_id_);
		buffer->bind();
		buffer->link_to(std::shared_ptr<vn::vertex_array>(this));

		unsigned int index = 0;
		for (auto& a: buffer->layout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, a.component_count(),
                  a.api_type(),
                  a.normalized ? GL_TRUE : GL_FALSE,
                  buffer->layout().stride(), (const void*)a.offset);

			++index;
		}

		vertex_buffers_.push_back(buffer);
	}

	void gl_vertex_array::add_index_buffer(const std::shared_ptr<vn::index_buffer> &buffer) {
		glBindVertexArray(renderer_id_);
		buffer->bind();

		index_buffers_.push_back(buffer);
	}

	void gl_vertex_array::bind() const {
		glBindVertexArray(renderer_id_);
	}

	void gl_vertex_array::unbind() const {
		glBindVertexArray(0);
	}
}
