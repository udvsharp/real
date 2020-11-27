// Copyright (c) 2020 udv. All rights reserved.

#include "real/transform.hpp"
#include "real/renderer/camera.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/renderer/render_command.hpp"
#include "real/renderer/light.hpp"
#include "real/api/gl/gl_renderer_api.hpp"

namespace Real
{
	// TODO: initialize dynamically
	RendererAPI* Renderer::api = new GLRendererApi {};
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData {};

	void Renderer::StartScene(Real::Camera& camera) noexcept
	{
		sceneData->viewprojection = camera.Viewprojection();
		sceneData->viewPosition = camera.Position();
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::EndScene() noexcept
	{

	}

	void Renderer::Submit(const Reference <VertexArray>& vao,
			const Real::Reference<Shader>& shader,
			const Real::Transform& model) noexcept
	{
		shader->Bind();
		shader->UniformFloat("u_viewPos", sceneData->viewPosition);
		shader->UniformMatrix("u_vp", sceneData->viewprojection);
		shader->UniformMatrix("u_model", model.Matrix());
		// TODO: implement render command queue
		RenderCommand::DrawIndexed(vao);
	}

//	void Renderer::Submit(const Real::Reference<Light>& light) noexcept
//	{
//		light->Bind();
//		light->UniformFloat("u_viewPos", sceneData->viewPosition);
//		light->UniformMatrix("u_vp", sceneData->viewprojection);
//		light->UniformMatrix("u_model", model.Matrix());
//		// TODO: implement render command queue
//		RenderCommand::DrawIndexed(vao);
//	}


	void Renderer::Submit(const Reference <VertexArray>& vao,
			const Real::Reference<Material>& material,
			const Real::Transform& model) noexcept
	{
		auto shader = material->Shader();
		shader->Bind();
		shader->UniformFloat("u_viewPos", sceneData->viewPosition);
		shader->UniformMatrix("u_vp", sceneData->viewprojection);
		shader->UniformMatrix("u_model", model.Matrix());
		// TODO: implement render command queue
		RenderCommand::DrawIndexed(vao);
	}
}
