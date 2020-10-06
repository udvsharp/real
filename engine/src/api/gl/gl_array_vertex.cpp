// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_array_vertex.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace real {
	gl_vertex_array::gl_vertex_array()
			: renderer_id_{ 0 }, vertex_buffers_{}, index_buffers_{}, count_{ 0 } {
		glGenVertexArrays(1, &renderer_id_);
	}

	gl_vertex_array::~gl_vertex_array() {
		glDeleteVertexArrays(1, &renderer_id_);
	}

	void gl_vertex_array::add_vertex_buffer(const real::reference<real::vertex_buffer> &buffer) {
		real_assert(!buffer->layout().attributes().empty(), "Vertex buffer has no layout!");

		glBindVertexArray(renderer_id_);
		buffer->bind();
		buffer->link_to(real::reference<real::vertex_array>(this));

		uint32_t index = 0;
		for (auto &a: buffer->layout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, a.component_count(),
			                      a.api_type(),
			                      a.normalized ? GL_TRUE : GL_FALSE,
			                      buffer->layout().stride(), (const void *) a.offset);

			++index;
		}

		vertex_buffers_.push_back(buffer);
	}

	void gl_vertex_array::add_index_buffer(const real::reference<real::index_buffer> &buffer) {
		glBindVertexArray(renderer_id_);
		buffer->bind();
		count_ += buffer->count();

		index_buffers_.push_back(buffer);
	}

	void gl_vertex_array::bind() const {
		glBindVertexArray(renderer_id_);
	}

	void gl_vertex_array::unbind() const {
		glBindVertexArray(0);
	}

	int32_t gl_vertex_array::count() const {
		return count_;
	}
}
