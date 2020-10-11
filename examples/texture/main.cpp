// Copyright (c) 2020 udv. All rights reserved.

#include <real/real.hpp>

class application : public real::application {
private:
	// Rendering
	real::reference<real::vertex_array> vao_;
	real::reference<real::vertex_buffer> vbo_;
	real::reference<real::index_buffer> ibo_;

	real::camera* camera_;

	real::reference<real::texture> texture_;
	real::reference<real::shader> shader_;
public:
	application() : real::application() {
		// layers().push_layer(new real::imgui_layer{});
		// Perspective
		camera_ = new real::camera_perspective{ 45.0f, 16.0f, 9.0f };

		// Orthographic
		// camera_ =  new real::camera_orthographic {-3.2f, 3.2f, -1.8f, 1.8f, };

		camera_->position( {0.0f, 0.0f, 5.0f} );
		camera_->look_at({ 0.0, 0.0, 0.0 });
	}
protected:
	// Override this if you want
	virtual void init() override {
		real::application::init();

		REAL_TRACE("Initializing shaders...");
		shader_.reset(real::shader::make());
		shader_->add_shader(GL_VERTEX_SHADER, "shaders/tex.vs.glsl");
		shader_->add_shader(GL_FRAGMENT_SHADER, "shaders/tex.fs.glsl");
		shader_->link();

		REAL_TRACE("Initializing textures...");
		texture_ = real::texture2d::make(std::string("assets/textures/checkerboard.png"));
		texture_->init();
		shader_->uniform_int("u_texture", 0);

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
		vao_.reset(real::vertex_array::make());
		vao_->bind();

		// Vertex Buffer
		vbo_.reset(real::vertex_buffer::make(vertices, sizeof(vertices)));
		vbo_->layout({
		    { real::shader_data_t::vec3, "_pos",  },
		    { real::shader_data_t::vec2, "_texcoord",},
		    // { real::shader_data_t::vec4, "_color",},
		});

		// Index Buffer
		ibo_.reset(real::index_buffer::make(positions, sizeof(positions) / sizeof(unsigned int)));
		ibo_->bind();

		// Link buffers to vertex array
		vao_->add_vertex_buffer(vbo_);
		vao_->add_index_buffer(ibo_);
		// endregion
	}

	virtual void update(real::timestep ts) override {}

	virtual void render(real::timestep ts) override {
		real::renderer::start_scene(*camera_);

		real::transform transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

		texture_->bind(0);
		real::renderer::submit(vao_, shader_, transform);
		real::renderer::end_scene();

		real::render_command::draw_indexed(vao_);
	}

	virtual void on_event(real::ev &e) override {
		real::application::on_event(e);
	}
};

real::application *real::create() {
	return new ::application();
}