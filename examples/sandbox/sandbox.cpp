// Copyright (c) 2020 udv. All rights reserved.

#include <version/version.hpp>

class application : public vn::application {
private:
	// Rendering
	std::shared_ptr<vn::vertex_array> vao_;
	std::shared_ptr<vn::vertex_buffer> vbo_;
	std::shared_ptr<vn::index_buffer> ibo_;
public:
	application() : vn::application() {
		// layers().push_layer(new vn::imgui_layer{});
	}
protected:
	// Override this if you want

	virtual void init() override {
		// region Setup rendering
		// Vertices
		float vertices[] = {
			// Positions           // Colors
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // FTR
			 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // FBR
			 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // FBL
			 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // FTL
			-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // RTR
			-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // RBR
			-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // RBL
			-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f, // RTL
		};

		unsigned int positions[]{
				0, 1, 2, 3, // Front
				4, 5, 6, 7, // Rear
				2, 3, 6, 7, // Left
				0, 1, 4, 5, // Right
				0, 3, 4, 7, // Top
				1, 2, 5, 6, // Bottom
		};

		// Vertex Array
		vao_.reset(vn::vertex_array::make());
		vao_->bind();

		// Vertex Buffer
		vbo_.reset(vn::vertex_buffer::make(vertices, sizeof(vertices)));
		vbo_->layout({
		    { vn::shader_data_t::vec3, "_pos",  },
		    { vn::shader_data_t::vec4, "_color",},
		});

		// Index Buffer
		ibo_.reset(vn::index_buffer::make(positions, sizeof(positions) / sizeof(unsigned int)));
		ibo_->bind();

		// Link buffers to vertex array
		vao_->add_vertex_buffer(vbo_);
		vao_->add_index_buffer(ibo_);
		// endregion
	}

	virtual void render() override {
		// camera_.rotation(45.0f);

		vn::renderer::start_scene(camera_);
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