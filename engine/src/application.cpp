// Copyright (c) 2020 udv. All rights reserved.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "version/application.hpp"
#include "version/logger.hpp"

namespace vn {

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {

		// Setup systems
		window_props props{};
		window_.reset(window::make(props));
		input_.reset(input::make());

		window_->set_ev_callback([this](ev &e) {
			application::on_event(e);
		});

		shader_ = shader {"shaders/base.vs.glsl", "shaders/base.fs.glsl"};

		// region Setup rendering
		// Vertices
		float vertices[] = {
				// Positions
				0.0f, 0.5f, 0.0f,
				0.0f, -0.5f, 0.0f,
				0.5f, 0.0f, 0.0f,
				-0.5f, 0.0f, 0.0f,
		};

		unsigned int positions[]{
				0, 1, 2,
				0, 1, 3
		};

		// TODO: setup Vertex Array
		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);
		// TODO: setup Vertex Buffer
		glGenBuffers(1, &vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		// TODO: setup Index Buffer
		glGenBuffers(1, &ibo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		// endregion
	}

	void application::tick() {
	}

	void application::run() {
		VN_CORE_TRACE("Application is running!");

		while (is_running_) {
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader_.bind();

			glBindVertexArray(vao_);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			for (auto *layer : layers_) {
				layer->update();
			}

			window_->on_update();
		}

		VN_CORE_TRACE("Closing application;");
	}

	void application::on_event(ev &e) {
		VN_CORE_TRACE("Got event: {0}", e);

		ev_dispatcher dispatcher{&e};
		dispatcher.dispatch<window_close_ev>([this](window_close_ev &event) -> bool {
			this->on_window_close(event);
			return false;
		});

		for (auto it = layers_.end(); it != layers_.begin();) {
			(*--it)->handle_event(e);
			if (e.handled()) {
				break;
			}
		}
	}

	void application::on_window_close(window_close_ev &e) {
		this->is_running_ = false;
	}
}

