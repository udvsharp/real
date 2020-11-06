// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERER_BASE
#define REAL_RENDERER_BASE

#include "real/transform.hpp"
#include "real/core.hpp"
#include "real/renderer/renderer_api.hpp"
#include "real/renderer/camera.hpp"
#include "real/renderer/base_shader.hpp"

namespace Real
{
	class REAL_API Renderer
	{
	public:
		[[nodiscard]] static inline RendererAPI& Api() noexcept
		{ return *api; }

		static void Init();
		static void StartScene(Camera& camera) noexcept;
		static void EndScene() noexcept;
		static void Submit(const Real::Reference<VertexArray>& vao,
				const Real::Reference<Shader>& shader,
				const Real::Transform& model) noexcept;
	private:
		static RendererAPI* api;

		// TODO: remove this COMPLETELY Temporary stuff
		struct SceneData
		{
			glm::mat4 viewprojection;
		};

		static SceneData* sceneData;
	};
}

#endif //REAL_RENDERER_BASE
