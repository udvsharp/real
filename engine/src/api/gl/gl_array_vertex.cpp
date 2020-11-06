// Copyright (c) 2020 udv. All rights reserved.

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_array_vertex.hpp"
#include "real/api/gl/gl_buffer_vertex.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace Real
{
	GLVertexArray::GLVertexArray()
			:rendererId { 0 }, vertexBuffers {}, indexBuffers {}, count { 0 }
	{
		glCreateVertexArrays(1, &rendererId);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererId);
	}

	void GLVertexArray::AddVertexBuffer(
			const Real::Reference<Real::VertexBuffer>& buffer)
	{
		real_msg_assert(!buffer->Layout().Attributes().empty(),
				"Vertex buffer has no Layout!");

		glBindVertexArray(rendererId);
		buffer->Bind();
		buffer->LinkTo(Real::Reference<Real::VertexArray>(this));

		uint32_t index = 0;
		for (auto& a: buffer->Layout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, a.component_count(),
					a.api_type(),
					a.normalized ? GL_TRUE : GL_FALSE,
					buffer->Layout().Stride(), (const void*)a.offset);

			++index;
		}

		vertexBuffers.push_back(buffer);
	}

	void
	GLVertexArray::AddIndexBuffer(const Real::Reference<Real::IndexBuffer>& buffer)
	{
		glBindVertexArray(rendererId);
		buffer->Bind();
		count += buffer->Count();

		indexBuffers.push_back(buffer);
	}

	void GLVertexArray::Bind() const
	{
		glBindVertexArray(rendererId);
	}

	void GLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	int32_t GLVertexArray::Count() const
	{
		return count;
	}
}
