// Copyright (c) 2020 udv. All rights reserved.

#include <utility>
#include "real/time/timestep.hpp"

#include "real/logger.hpp"
#include "real/event.hpp"
#include "real/platform/windows/windows_window.hpp"

namespace real::platform {

	static bool s_glfw_initialized = false;

	void glfw_error_callback(int32_t code, const char *msg) {
		REAL_CORE_ERROR("GLFW Error: ({:#x}) {}", code, msg);
	}

	window::window(window_data data)
			: native_window_{ nullptr }, rendering_context_{ nullptr }, data_(std::move(data)) {
	}

	void window::init() {
		if (!s_glfw_initialized) {
			REAL_CORE_TRACE("Initializing GLFW...");

			if (glfwInit() == GLFW_TRUE) {
				s_glfw_initialized = true;
				REAL_CORE_INFO("Successfully initialized GLFW");
			} else {
				REAL_CORE_ERROR("Couldn't initialize GLFW!");
			}

			glfwSetErrorCallback(glfw_error_callback);
		}

		REAL_CORE_TRACE("Creating window: {0}, {1}, {2}", data_.title, data_.width, data_.height);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Testing
		// Antialiasing
		glfwWindowHint(GLFW_SAMPLES, 4);
		native_window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
		// TODO: abstract api
		rendering_context_ = new gl_rendering_context{ native_window_ };
		rendering_context_->init();

		// Extensions
		glEnable(GL_MULTISAMPLE);

		glfwSetWindowUserPointer(native_window_, &data_);
		vsync_native(data_.is_v_sync);

		// GLFW callbacks
		glfwSetWindowSizeCallback(native_window_, [](GLFWwindow *window, int width, int height) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			data.width = width;
			data.height = height;

			window_resize_ev ev{ static_cast<window_dimension_t>(width), static_cast<window_dimension_t>(height) };
			data.ev_callback(ev);
		});

		glfwSetWindowCloseCallback(native_window_, [](GLFWwindow *window) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			window_close_ev ev{};
			data.ev_callback(ev);
		});

		glfwSetKeyCallback(native_window_, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					key_press_ev event(key);
					data.ev_callback(event);
					break;
				}
				case GLFW_RELEASE: {
					key_release_ev event(key);
					data.ev_callback(event);
					break;
				}
				case GLFW_REPEAT: {
					key_press_ev event(key);
					data.ev_callback(event);
					break;
				}
				default: {
					REAL_CORE_ERROR("Unknown key action: {}", action);
				}
			}
		});

		glfwSetCharCallback(native_window_, [](GLFWwindow *window, uint32_t character) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);
			key_typed_ev ev(character);
			data.ev_callback(ev);
		});

		glfwSetMouseButtonCallback(native_window_, [](GLFWwindow *window, int button, int action, int mods) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					mouse_btn_press_ev event(button);
					data.ev_callback(event);
					break;
				}
				case GLFW_RELEASE: {
					mouse_btn_release_ev event(button);
					data.ev_callback(event);
					break;
				}
				default: {
					REAL_CORE_ERROR("Unknown key action: {}", action);
				}
			}
		});

		glfwSetScrollCallback(native_window_, [](GLFWwindow *window, double xOffset, double yOffset) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			mouse_scroll_ev event((float) xOffset, (float) yOffset);
			data.ev_callback(event);
		});

		glfwSetCursorPosCallback(native_window_, [](GLFWwindow *window, double xPos, double yPos) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			mouse_move_ev event((float) xPos, (float) yPos);
			data.ev_callback(event);
		});
	}

	window::~window() {
		::real::window::~window();
		REAL_CORE_TRACE("Destroying native window");
		glfwDestroyWindow(native_window_);
		glfwTerminate(); // TODO: terminate GLFW in rendering context?
	}

	void window::on_update(timestep ts) {
		::real::window::on_update(ts);
		glfwPollEvents();
		rendering_context_->swap_buffers();
	}

	void window::vsync_native(bool enabled) {
		rendering_context_->vsync(enabled);
	}

	void window::vsync(bool enabled) {
		vsync_native(enabled);
		data_.is_v_sync = enabled;
	}

	void window::ev_callback(const ev_callback_t &callback) {
		data_.ev_callback = callback;
	}
}