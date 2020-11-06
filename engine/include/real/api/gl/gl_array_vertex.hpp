// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_ARRAY_VERTEX
#define REAL_GL_ARRAY_VERTEX

#include "real/core.hpp"
#include "real/renderer/array_vertex.hpp"

namespace Real
{
	class REAL_API GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		~GLVertexArray() override;

		[[nodiscard]] virtual const std::vector<Real::Reference<Real::VertexBuffer>>& VertexBuffers() const override
		{ return vertexBuffers; };
		[[nodiscard]] virtual const std::vector<Real::Reference<Real::IndexBuffer>>& IndexBuffers() const override
		{ return indexBuffers; };

		virtual void AddVertexBuffer(
				const Real::Reference<Real::VertexBuffer>& buffer) override;
		virtual void AddIndexBuffer(
				const Real::Reference<Real::IndexBuffer>& buffer) override;

		virtual int32_t Count() const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		renderer_id_t rendererId;
		uint32_t count;

		std::vector<Real::Reference<VertexBuffer>> vertexBuffers;
		std::vector<Real::Reference<IndexBuffer>> indexBuffers;
	};
}

#endif //REAL_GL_ARRAY_VERTEX
