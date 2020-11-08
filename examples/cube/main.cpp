// Copyright (c) 2020 udv. All rights reserved.

#include <real/real.hpp>

class Application : public Real::Application
{
private:
	// Rendering
	Real::Reference<Real::VertexArray> vao;
	Real::Reference<Real::VertexBuffer> vbo;
	Real::Reference<Real::IndexBuffer> ibo;

	Real::Camera* camera;

	Real::ShaderLibrary shaderLib;
public:
	Application()
			:Real::Application()
	{
		// layers().push_layer(new real::imgui_layer{});
		// Perspective
		camera = new Real::PerspectiveCamera { 45.0f, 16.0f, 9.0f };

		// Orthographic
		// camera =  new Real::OrghographicCamera {-3.2f, 3.2f, -1.8f, 1.8f, };
	}
protected:
	// Override this if you want
	virtual void Init() override
	{
		shaderLib.Load("shaders/base.glsl");

		// region Setup rendering
		// Vertices
		// TODO: fix colors
		float vertices[] = {
				// Positions           // Colors
				 1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 0.0f, 0.5f, // FTR
				 1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 0.0f, 0.5f, // FBR
				-1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 0.5f, // FBL
				-1.0f,  1.0f,  1.0f,    0.5f, 0.5f, 0.5f, 0.5f, // FTL
				 1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 0.0f, 0.5f, // RTR
				 1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 0.5f, // RBR
				-1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 0.5f, // RBL
				-1.0f,  1.0f, -1.0f,    0.5f, 0.5f, 0.5f, 0.5f, // RTL
		};

		unsigned int positions[] {
				0, 1, 2, 0, 2, 3, // Front  0 1 2 3
				4, 5, 6, 4, 6, 7, // Rear   4 5 6 7
				2, 3, 6, 3, 6, 7, // Left   2 3 6 7
				0, 1, 4, 1, 4, 5, // Right  0 1 4 5
				0, 3, 4, 3, 4, 7, // Top    0 3 4 7
				1, 2, 5, 2, 5, 6, // Bottom 1 2 5 6
		};

		// Vertex Array
		vao = Real::Reference<Real::VertexArray> { Real::VertexArray::Make() };

		// Vertex Buffer
		vbo = Real::Reference<Real::VertexBuffer> {
				Real::VertexBuffer::Make(vertices, sizeof(vertices)) };
		vbo->Layout({
				{ Real::shader_data_t::vec3, "_pos", },
				{ Real::shader_data_t::vec4, "_color", },
		});

		// Index Buffer
		ibo = Real::Reference<Real::IndexBuffer> { Real::IndexBuffer::Make(positions,
				sizeof(positions) / sizeof(unsigned int)) };

		// Link buffers to vertex array
		vao->AddVertexBuffer(vbo);
		vao->AddIndexBuffer(ibo);
		// endregion
	}

	virtual void Update(Real::Timestep ts) override
	{
		// rotation
		// REAL_INFO("Frame Delta time: {}", ts.seconds());

		const float radius = 5.0f;
		const float speed = 0.5f;
		float cx = glm::sin(Real::Time() * speed) * radius;
		float cz = glm::cos(Real::Time() * speed) * radius;

		camera->Position({ cx, 3.0f, cz });
		camera->LookAt({ 0.0, 0.0, 0.0 });
	}

	virtual void Render(Real::Timestep ts) override
	{
		Real::Renderer::StartScene(*camera);

		Real::Transform transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.2f));

		Real::Renderer::Submit(vao, shaderLib.Get("base"), transform);
		Real::Renderer::EndScene();

		Real::RenderCommand::DrawIndexed(vao);
	}

	virtual void OnEvent(Real::Event& e) override
	{
		Real::Application::OnEvent(e);
	}
};

Real::Application* Real::Make()
{
	return new ::Application();
}