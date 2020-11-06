// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace Real
{

	GLIndexBuffer::GLIndexBuffer(uint32_t* data, uint32_t size)
			:rendererId { 0 }, count { size }
	{
		glCreateBuffers(1, &rendererId);
		// TODO: remove hardcoded buffer data usage
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data,
				GL_DYNAMIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererId);
	}

	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	}

	void GLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t GLIndexBuffer::Count() const
	{
		return count;
	}
}
