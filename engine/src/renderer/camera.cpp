// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/matrix_transform.hpp>

#include "real/renderer/camera.hpp"

namespace Real
{
	// region Camera
	Camera::Camera(const glm::mat4& projection, glm::vec3 position, glm::vec3 direction)
			:position { position }, projection { projection }, direction { direction }
	{}

	void Camera::Update()
	{
		UpdateView();
		UpdateViewprojection();
	}

	void Camera::Init()
	{
		Update();
	}

	void Camera::UpdateViewprojection()
	{
		// OpenGL needs this order.
		cacheViewprojection = projection * view;
	}

	glm::vec3 Camera::Up() const
	{
		return glm::cross(Direction(), Right());
	}

	glm::vec3 Camera::Right() const
	{
		return glm::normalize(glm::cross({ 0.0f, 1.0f, 0.0f }, Direction()));
	}

	glm::vec3 Camera::Direction() const
	{
		return direction;
	}

	glm::vec3 Camera::DirectionTo(glm::vec3 target) const
	{
		return glm::normalize(position - target);
	}

	void Camera::LookAt(glm::vec3 target)
	{
		direction = DirectionTo(target);
		view = glm::lookAt(position, target, Up());
		UpdateViewprojection();
	}
	// endregion

	//region Orthographic camera
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
			float top)
			:Camera { glm::ortho(left, right, bottom, top, 0.1f, 10.0f) }
	{
	}

	void OrthographicCamera::UpdateView()
	{
		// TODO: improve this
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position) *
						glm::rotate(glm::identity<glm::mat4>(), glm::radians(0.0f),
								glm::vec3(0, 0, 1));

		view = glm::inverse(transform);
	}

	//endregion
	//region Perspective camera
	PerspectiveCamera::PerspectiveCamera(float yfov, float w, float h)
			:Camera { glm::perspective(glm::radians(yfov), w / h, 0.1f, 10.0f) }
	{
	}

	void PerspectiveCamera::UpdateView()
	{
		// TODO: improve this
		glm::mat4 transform =
				glm::translate(glm::identity<glm::mat4>(), position) *
						glm::rotate(glm::identity<glm::mat4>(), glm::radians(0.0f),
								glm::vec3(0, 0, 1));

		view = glm::inverse(transform);
	}

	//endregion
}
