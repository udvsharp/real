// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/matrix_transform.hpp>

#include "version/renderer/camera.hpp"

namespace vn {
	// region Camera
	camera::camera(const glm::mat4 &projection, glm::vec3 position, glm::vec3 direction)
			: position_{ position }, projection_{ projection }, direction_ { direction } {}

	void camera::update() {
		update_view();
		update_viewprojection();
	}

	void camera::init() {
		update();
	}

	void camera::update_viewprojection() {
		// OpenGL needs this order.
		cache_viewprojection_ = projection_ * view_;
	}

	glm::vec3 camera::up() const {
		return glm::cross(direction(), right());
	}

	glm::vec3 camera::right() const {
		return glm::normalize(glm::cross({ 0.0f, 1.0f, 0.0f }, direction()));
	}

	glm::vec3 camera::direction() const {
		return direction_;
	}

	glm::vec3 camera::direction_to(glm::vec3 target) const {
		return glm::normalize(position_ - target);
	}

	void camera::look_at(glm::vec3 target) {
		direction_ = direction_to(target);
		view_ = glm::lookAt(position_, target, up());
		update_viewprojection();
	}
	// endregion

	//region Orhographic camera
	camera_orthographic::camera_orthographic(float left, float right, float bottom, float top)
			: camera{ glm::ortho(left, right, bottom, top, 0.1f, 10.0f) } {
	}

	void camera_orthographic::update_view() {
		// TODO: improve this
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position_) *
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(0.0f), glm::vec3(0, 0, 1));

		view_ = glm::inverse(transform);
	}

	//endregion
	//region Perspective camera
	camera_perspective::camera_perspective(float yfov, float w, float h)
			: camera{ glm::perspective(glm::radians(yfov), w / h, 0.1f, 10.0f) } {
	}

	void camera_perspective::update_view() {
		// TODO: improve this
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position_) *
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(0.0f), glm::vec3(0, 0, 1));

		view_ = glm::inverse(transform);
	}

	//endregion
}
