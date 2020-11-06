// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDER_COMMAND
#define REAL_RENDER_COMMAND

#include <memory>

#include "real/core.hpp"
#include "real/renderer/array_vertex.hpp"

namespace Real
{
	class REAL_API RenderCommand
	{
	public:
		static inline void ClearColor(glm::fvec4 color)
		{
			Renderer::Api().ClearColor(color);
		}

		static void Init()
		{
			Renderer::Api().Init();
		}

		static inline void Clear()
		{
			Renderer::Api().clear();
		}

		static inline void DrawIndexed(const Real::Reference<VertexArray>& vertexArray)
		{
			Renderer::Api().DrawIndexed(vertexArray);
		}
	};
}

#endif //REAL_RENDER_COMMAND
