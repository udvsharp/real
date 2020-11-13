// Copyright (c) 2020 udv. All rights reserved.

#include <real/real.hpp>
#include <imgui.h> // TODO: abstract imgui
#include <glm/gtc/type_ptr.hpp>

class SandboxLayer : public Real::Layer
{
private:
	glm::vec4 color;

	// Rendering
	Real::Reference<Real::VertexArray> vao;
	Real::Camera* camera;
	Real::ShaderLibrary shaderLib;
public:
	SandboxLayer()
			:Real::Layer()
	{
		// Perspective
		camera = new Real::PerspectiveCamera { 45.0f, 16.0f, 9.0f };
		color = { 1.0f, 1.0f, 1.0f, 1.0f, };

		// Orthographic
		// camera =  new Real::OrghographicCamera {-3.2f, 3.2f, -1.8f, 1.8f, };
	}

	virtual void OnImGUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(color));
		ImGui::End();
	}

	virtual void Attach() override
	{
		auto shader = shaderLib.Load("shaders/material.glsl");

		// region Setup rendering
		// Vertices
		// @formatter:off
		float vertices[] = {
				// TOP
				// Positions           // Normals             // Colors
				 1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,   // 1.0f, 0.0f, 0.0f, 1.0f, // FTR
				-1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,   // 1.0f, 0.0f, 0.0f, 1.0f, // FTL
				 1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,   // 1.0f, 0.0f, 0.0f, 1.0f, // RTR
				-1.0f,  1.0f, -1.0f,    0.0f,  1.0f,  0.0f,   // 1.0f, 0.0f, 0.0f, 1.0f, // RTL

				// BOTTOM
				// Positions           // Normals             // Colors
				 1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,   // 0.0f, 1.0f, 0.0f, 1.0f, // FBR
				-1.0f, -1.0f,  1.0f,    0.0f, -1.0f,  0.0f,   // 0.0f, 1.0f, 0.0f, 1.0f, // FBL
				 1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,   // 0.0f, 1.0f, 0.0f, 1.0f, // RBR
				-1.0f, -1.0f, -1.0f,    0.0f, -1.0f,  0.0f,   // 0.0f, 1.0f, 0.0f, 1.0f, // RBL

				// FRONT
				// Positions           // Normals             // Colors
				 1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,   // 0.0f, 0.0f, 1.0f, 1.0f, // FTR
				-1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,   // 0.0f, 0.0f, 1.0f, 1.0f, // FTL
				 1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,   // 0.0f, 0.0f, 1.0f, 1.0f, // FBR
				-1.0f, -1.0f,  1.0f,    0.0f,  0.0f,  1.0f,   // 0.0f, 0.0f, 1.0f, 1.0f, // FBL

				// BACK
				// Positions           // Normals             // Colors
				 1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,   // 0.5f, 0.5f, 0.0f, 1.0f, // RTR
				-1.0f,  1.0f, -1.0f,    0.0f,  0.0f, -1.0f,   // 0.5f, 0.5f, 0.0f, 1.0f, // RTL
				 1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,   // 0.5f, 0.5f, 0.0f, 1.0f, // RBR
				-1.0f, -1.0f, -1.0f,    0.0f,  0.0f, -1.0f,   // 0.5f, 0.5f, 0.0f, 1.0f, // RBL

				// LEFT
				// Positions           // Normals             // Colors
				-1.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,   // 0.0f, 0.5f, 0.5f, 1.0f, // FTL
				-1.0f, -1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,   // 0.0f, 0.5f, 0.5f, 1.0f, // FBL
				-1.0f,  1.0f, -1.0f,   -1.0f,  0.0f,  0.0f,   // 0.0f, 0.5f, 0.5f, 1.0f, // RTL
				-1.0f, -1.0f, -1.0f,   -1.0f,  0.0f,  0.0f,   // 0.0f, 0.5f, 0.5f, 1.0f, // RBL

				// RIGHT
				// Positions           // Normals             // Colors
			 	 1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,   // 0.5f, 0.0f, 0.5f, 1.0f, // FTR
			 	 1.0f, -1.0f,  1.0f,    1.0f,  0.0f,  0.0f,   // 0.5f, 0.0f, 0.5f, 1.0f, // FBR
			 	 1.0f,  1.0f, -1.0f,    1.0f,  0.0f,  0.0f,   // 0.5f, 0.0f, 0.5f, 1.0f, // RTR
			 	 1.0f, -1.0f, -1.0f,    1.0f,  0.0f,  0.0f,   // 0.5f, 0.0f, 0.5f, 1.0f, // RBR
		};

		unsigned int positions[] {
				0,  1,  2,    1,  2,  3,   // TOP
				4,  5,  6,    5,  6,  7,   // BOTTOM
				8,  9, 10,    9, 10, 11,   // FRONT
				12, 13, 14,   13, 14, 15,   // BACK
				16, 17, 18,   17, 18, 19,   // LEFT
				20, 21, 22,   21, 22, 23,   // RIGHT
		};
		// @formatter:on


		// Vertex Array
		vao = Real::VertexArray::Make();

		// Vertex Buffer
		Real::Reference<Real::VertexBuffer> vbo = Real::VertexBuffer::Make(vertices,
				sizeof(vertices));
		vbo->Layout({
				{ Real::shader_data_t::vec3, "_pos", },
				{ Real::shader_data_t::vec3, "_normal", },
//				{ Real::shader_data_t::vec4, "_color", },
		});

		// Index Buffer
		Real::Reference<Real::IndexBuffer> ibo = Real::IndexBuffer::Make(positions,
				sizeof(positions) / sizeof(unsigned int));

		// Link buffers to vertex array
		vao->AddVertexBuffer(vbo);
		vao->AddIndexBuffer(ibo);
		// endregion

		shader->Bind();
		shader->UniformFloat("u_lightColor", { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	virtual void Update(Real::Timestep ts) override
	{
		// TODO: abstract render from calculations
		// rotation
		const float radius = 5.0f;
		const float speed = 0.5f;
		float cx = glm::sin(Real::Time() * speed) * radius;
		float cz = glm::cos(Real::Time() * speed) * radius;

		camera->Position({ cx, 3.0f, cz });
		camera->LookAt({ 0.0, 0.0, 0.0 });

		// Scene
		Real::Renderer::StartScene(*camera);

		Real::Transform transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.2f));

		const auto& shader = shaderLib.Get("material");
		shader->UniformFloat("u_color", color);

		Real::Renderer::Submit(vao, shader, transform);
		Real::Renderer::EndScene();

		Real::RenderCommand::DrawIndexed(vao);
	}
};

class Application : public Real::Application
{
public:
	Application()
			:Real::Application()
	{
		PushLayer(new SandboxLayer());
	}
};

Real::Scope<Real::Application> Real::Make()
{
	return Real::MakeScope<::Application>();
}