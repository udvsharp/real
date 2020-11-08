// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_VERTEX_ARRAY
#define REAL_VERTEX_ARRAY

#include <memory>

#include "real/core.hpp"

namespace Real
{
	class VertexBuffer;
	class IndexBuffer;

	class REAL_API VertexArray
	{
	public:
		virtual ~VertexArray();

		[[nodiscard]] virtual const std::vector<Real::Reference<Real::VertexBuffer>>&
		VertexBuffers() const = 0;
		[[nodiscard]] virtual const std::vector<Real::Reference<Real::IndexBuffer>>&
		IndexBuffers() const = 0;

		virtual void AddVertexBuffer(
				const Real::Reference<Real::VertexBuffer>& buffer) = 0;
		virtual void AddIndexBuffer(
				const Real::Reference<Real::IndexBuffer>& buffer) = 0;

		virtual int32_t Count() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		static Real::Scope<VertexArray> Make();
	};
}

#endif //REAL_VERTEX_ARRAY
