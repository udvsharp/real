// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/matrix_transform.hpp>

#include "version/renderer/camera.hpp"


namespace vn {
	camera::camera(float left, float right, float bottom, float top)
			: projection_{glm::ortho(left, right, bottom, top, -1.0f, 1.0f)},
			view_ { glm::identity<glm::mat4>() } {
		update();
	}

	void camera::update() {
		update_view();
		update_viewprojection();
	}

	void camera::update_view() {
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position_) *
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(rotation_), glm::vec3(0, 0, 1));

		view_ = glm::inverse(transform);
	}

	void camera::update_viewprojection() {
		// OpenGL needs this order.
		cache_viewprojection_ = projection_ * view_;
	}
}
