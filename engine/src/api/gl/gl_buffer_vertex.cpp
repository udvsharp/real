// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"

namespace Real
{

	GLVertexBuffer::GLVertexBuffer(float* data, uint32_t size)
			:rendererId { 0 }, bufferLayout {}, vertexArray { nullptr }
	{
		glCreateBuffers(1, &rendererId);
		// TODO: remove hardcoded buffer data usage
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererId);
	}

	void GLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	}

	void GLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLVertexBuffer::Layout(std::initializer_list<VertexAttribute> attributes)
	{
		bufferLayout = BufferLayout { attributes };
	}

	void GLVertexBuffer::LinkTo(const Real::Reference<Real::VertexArray>& vao)
	{
		this->vertexArray = vao;
	}
}
