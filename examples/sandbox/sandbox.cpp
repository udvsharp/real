// Copyright (c) 2020 udv. All rights reserved.

#include <version/version.hpp>
#include <cmath>

class application : public vn::application {
private:
	// Rendering
	std::shared_ptr<vn::vertex_array> vao_;
	std::shared_ptr<vn::vertex_buffer> vbo_;
	std::shared_ptr<vn::index_buffer> ibo_;

	vn::camera* camera_;

	std::shared_ptr<vn::shader> shader_;
public:
	application() : vn::application() {
		// layers().push_layer(new vn::imgui_layer{});
		// Pesrspective
		camera_ = new vn::camera_perspective{ 45.0f, 16.0f, 9.0f };

		// Orthographic
		// camera_ =  new vn::camera_orthographic {-3.2f, 3.2f, -1.8f, 1.8f, };
	}
protected:
	// Override this if you want
	virtual void init() override {
		vn::application::init();
		shader_.reset(new vn::shader{});
		shader_->add_shader(GL_VERTEX_SHADER, "shaders/base.vs.glsl");
		shader_->add_shader(GL_FRAGMENT_SHADER, "shaders/base.fs.glsl");
		shader_->link();

		// region Setup rendering
		// Vertices
		float vertices[] = {
			// Positions           // Colors
			 1.0f,  1.0f,  1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // FTR
			 1.0f, -1.0f,  1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // FBR
			-1.0f, -1.0f,  1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // FBL
			-1.0f,  1.0f,  1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // FTL
			 1.0f,  1.0f, -1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // RTR
			 1.0f, -1.0f, -1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // RBR
			-1.0f, -1.0f, -1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // RBL
			-1.0f,  1.0f, -1.0f,   // 1.0f, 1.0f, 1.0f, 1.0f, // RTL
		};

		unsigned int positions[]{
				0, 1, 2, 0, 2, 3, // Front  0 1 2 3
				4, 5, 6, 4, 6, 7, // Rear   4 5 6 7
				2, 3, 6, 3, 6, 7, // Left   2 3 6 7
				0, 1, 4, 1, 4, 5, // Right  0 1 4 5
				0, 3, 4, 3, 4, 7, // Top    0 3 4 7
				1, 2, 5, 2, 5, 6, // Bottom 1 2 5 6
		};

		// Vertex Array
		vao_.reset(vn::vertex_array::make());
		vao_->bind();

		// Vertex Buffer
		vbo_.reset(vn::vertex_buffer::make(vertices, sizeof(vertices)));
		vbo_->layout({
		    { vn::shader_data_t::vec3, "_pos",  },
		    // { vn::shader_data_t::vec4, "_color",},
		});

		// Index Buffer
		ibo_.reset(vn::index_buffer::make(positions, sizeof(positions) / sizeof(unsigned int)));
		ibo_->bind();

		// Link buffers to vertex array
		vao_->add_vertex_buffer(vbo_);
		vao_->add_index_buffer(ibo_);
		// endregion
	}

	virtual void update(vn::timestep ts) override {
		// rotation
		// VN_INFO("Frame Delta time: {}", ts.seconds());

		const float radius = 5.0f;
		const float speed = 0.5f;
		float cx = std::sin(vn::time() * speed) * radius;
		float cz = std::cos(vn::time() * speed) * radius;

		// TODO: add Y axis
		camera_->position( {cx, 3.0f, cz} );
		camera_->look_at({ 0.0, 0.0, 0.0 });
	}

	virtual void render(vn::timestep ts) override {
		vn::renderer::start_scene(*camera_);
		vn::renderer::submit(vao_, shader_);
		vn::renderer::end_scene();

		vn::render_command::draw_indexed(vao_);
	}

	virtual void on_event(vn::ev &e) override {
		vn::application::on_event(e);
	}
};

vn::application *vn::create() {
	VN_TRACE("Creating application...");
	return new ::application();
}