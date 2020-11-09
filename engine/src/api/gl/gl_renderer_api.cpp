// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>

#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_renderer_api.hpp"

namespace Real
{

	void GLRendererApi::Init()
	{
		// Multisampling
		glEnable(GL_MULTISAMPLE);

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Extensions
		glEnable(GL_EXT_direct_state_access);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
	}

	void GLRendererApi::ClearColor(glm::fvec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRendererApi::Clear(int32_t bits)
	{
		glClear(bits);
	}

	void GLRendererApi::DrawIndexed(const Real::Reference<VertexArray>& vao)
	{
		vao->Bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // TODO: remove poly mode
		// glEnable(GL_DEPTH_TEST);
		// TODO: remove hardcoded mode
		glDrawElements(GL_TRIANGLES, vao->Count(), GL_UNSIGNED_INT, nullptr);
	}

	RendererAPI::API GLRendererApi::Value() const
	{
		return API::GL;
	}

	int32_t GLRendererApi::DefaultClearBits() const noexcept
	{
		return (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
