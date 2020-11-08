// Copyright (c) 2020 udv. All rights reserved.

#include <real/real.hpp>

// #define TEXTURE_FILENAME "assets/textures/checkerboard.png"
#define TEXTURE_FILENAME "assets/textures/parrot.gif" // LOL this is bad texture...............

class Application : public Real::Application {
private:
	// Rendering
	Real::Reference<Real::VertexArray> vao;
	Real::Reference<Real::VertexBuffer> vbo;
	Real::Reference<Real::IndexBuffer> ibo;

	Real::Camera* camera;

	Real::Reference<Real::Texture> texture;
	Real::ShaderLibrary shaderLib;
public:
	Application() :Real::Application() {
		// layers().push_layer(new real::imgui_layer{});
		// Perspective
		camera = new Real::PerspectiveCamera{ 45.0f, 16.0f, 9.0f };

		// Orthographic
		// camera_ =  new real::camera_orthographic {-3.2f, 3.2f, -1.8f, 1.8f, };

		camera->Position({ 0.0f, 0.0f, 5.0f });
		camera->LookAt({ 0.0, 0.0, 0.0 });
	}
protected:
	// Override this if you want
	virtual void Init() override {
		Real::Application::Init();

		REAL_TRACE("Initializing shaders...");
		auto shader = shaderLib.Load("shaders/tex.glsl");

		REAL_TRACE("Initializing textures...");
		texture = Real::Texture2D::Make(std::string(TEXTURE_FILENAME));
		texture->Init();
		shader->UniformInt("u_texture", 0);

		// region Setup rendering
		// Vertices
		float vertices[] = {
			// Positions           // Texture coords   // Colors
			 1.0f,  1.0f,  1.0f,   1.0f,  1.0f,        // 1.0f, 1.0f, 1.0f, 1.0f, // TR
			 1.0f, -1.0f,  1.0f,   1.0f,  0.0f,        // 1.0f, 1.0f, 1.0f, 1.0f, // BR
			-1.0f, -1.0f,  1.0f,   0.0f,  0.0f,        // 1.0f, 1.0f, 1.0f, 1.0f, // BL
			-1.0f,  1.0f,  1.0f,   0.0f,  1.0f,        // 1.0f, 1.0f, 1.0f, 1.0f, // TL
		};

		unsigned int positions[]{
				0, 1, 2, 0, 2, 3, // Front  0 1 2 3
		};

		// Vertex Array
		vao = Real::VertexArray::Make();

		// Vertex Buffer
		vbo = Real::VertexBuffer::Make(vertices, sizeof(vertices));
		vbo->Layout({
				{ Real::shader_data_t::vec3, "_pos", },
				{ Real::shader_data_t::vec2, "_texcoord", },
				// { real::shader_data_t::vec4, "_color",},
		});

		// Index Buffer
		ibo = Real::IndexBuffer::Make(positions, sizeof(positions) / sizeof(unsigned int));

		// Link buffers to vertex array
		vao->AddVertexBuffer(vbo);
		vao->AddIndexBuffer(ibo);
		// endregion
	}

	virtual void Update(Real::Timestep ts) override {}

	virtual void Render(Real::Timestep ts) override {
		Real::Renderer::StartScene(*camera);

		Real::Transform transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		texture->Bind(0);
		Real::Renderer::Submit(vao, shaderLib.Get("tex"), transform);
		Real::Renderer::EndScene();

		Real::RenderCommand::DrawIndexed(vao);
	}

	virtual void OnEvent(Real::Event &e) override {
		Real::Application::OnEvent(e);
	}
};

Real::Scope<Real::Application> Real::Make() {
	return Real::MakeScope<::Application>();
}