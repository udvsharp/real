// Copyright (c) 2020 udv. All rights reserved.

#include <utility>

#include "version/logger.hpp"
#include "version/event.hpp"
#include "version/window/windows_window.hpp"

namespace vn::platform {

	// TODO: other APIs?
	static bool s_glfw_initialized = false;

	window::window(window_data data) : data_(std::move(data)) {
		if (!s_glfw_initialized) {
			VN_CORE_TRACE("Initializing GLFW");

			int success = glfwInit();

			if (success) {
				s_glfw_initialized = true;
			} else {
				VN_CORE_ERROR("Couldn't initialize GLFW!");
			}
		}

		VN_CORE_TRACE("Creating window: {0}, {1}, {2}", data_.title, data_.width, data_.height);

		native_window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(native_window_);
		glfwSetWindowUserPointer(native_window_, &data_);
		set_v_sync_native(data_.is_v_sync);

		// Glad
		if (!gladLoadGL()) {
			VN_CORE_ERROR("Couldn't load GL!");
		}

		// GLFW callbacks
		glfwSetWindowSizeCallback(native_window_, [](GLFWwindow *window, int width, int height) {
			window_data &data = *(window_data *) glfwGetWindowUserPointer(window);

			data.width = width;
			data.height = height;

			window_resize_ev ev{static_cast<window_dimension_t>(width), static_cast<window_dimension_t>(height)};
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
					VN_CORE_ERROR("Unknown key action: {}", action);
				}
			}
		});

		glfwSetCharCallback(native_window_, [](GLFWwindow *window, unsigned int character) {
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
					VN_CORE_ERROR("Unknown key action: {}", action);
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
		::vn::window::~window();
		VN_CORE_TRACE("Destroying native window");
		glfwDestroyWindow(native_window_);
		glfwTerminate(); // TODO: move this to the right place
	}

	void window::on_update() {
		::vn::window::on_update();
		glfwPollEvents();
		glfwSwapBuffers(native_window_);
	}

	void window::set_v_sync_native(bool enabled) {
		// TODO: read about that
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}

	void window::set_v_sync(bool enabled) {
		set_v_sync_native(enabled);

		data_.is_v_sync = enabled;
	}

	void window::set_ev_callback(const ev_callback_t &callback) {
		data_.ev_callback = callback;
	}
}