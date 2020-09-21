// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/matrix_transform.hpp>

#include "version/renderer/camera.hpp"


namespace vn {
	//region Orhographic camera
	camera_orthographic::camera_orthographic(float left, float right, float bottom, float top)
			: projection_{glm::ortho(left, right, bottom, top, -1.0f, 1.0f)},
			view_ { glm::identity<glm::mat4>() } {
		update();
	}

	void camera_orthographic::update() {
		update_view();
		update_viewprojection();
	}

	void camera_orthographic::update_view() {
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position_) *
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(rotation_), glm::vec3(0, 0, 1));

		view_ = glm::inverse(transform);
	}

	void camera_orthographic::update_viewprojection() {
		// OpenGL needs this order.
		cache_viewprojection_ = projection_ * view_;
	}
	//endregion
	//region Perspective camera
	camera_perspective::camera_perspective(float yfov, float w, float h)
			: projection_{glm::perspective(glm::radians(yfov), w / h, 1.0f, 100.0f)},
			  view_ { glm::identity<glm::mat4>() } {
		update();
	}

	void camera_perspective::update() {
		update_view();
		update_viewprojection();
	}

	void camera_perspective::update_view() {
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position_) *
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(rotation_), glm::vec3(0, 0, 1));

		view_ = glm::inverse(transform);
	}

	void camera_perspective::update_viewprojection() {
		// OpenGL needs this order.
		cache_viewprojection_ = projection_ * view_;
	}
	//endregion
}