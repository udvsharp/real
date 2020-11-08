// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_CAMERA
#define REAL_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "real/core.hpp"

namespace Real
{
	class REAL_API Camera
	{
	protected:
		glm::mat4 view;
		glm::mat4 projection;

		glm::mat4 cacheViewprojection;

		// TODO: migrate to quaternions
		glm::vec3 position;
		glm::vec3 direction;
	public:
		explicit Camera(const glm::mat4& projection = glm::identity<glm::mat4>(),
				glm::vec3 position = { 0.0f, 0.0f, 0.0f, },
				glm::vec3 direction = { 0.0f, 0.0f, 0.0f, });

		virtual void Init();

		[[nodiscard]] virtual glm::vec3 Position() const noexcept
		{ return this->position; };
		virtual void Position(glm::vec3 _position) noexcept
		{
			this->position = _position;
			Update();
		};

		[[nodiscard]] glm::mat4 Projection() const noexcept
		{ return this->projection; };
		virtual void Projection(glm::mat4 _projection) noexcept
		{
			this->projection = _projection;
			UpdateViewprojection();
		};

		[[nodiscard]] virtual glm::mat4 View() const noexcept
		{ return this->view; };
		[[nodiscard]] virtual glm::mat4 Viewprojection() const noexcept
		{ return this->cacheViewprojection; };

		virtual void LookAt(glm::vec3 target);
	protected:
		virtual void Update();
		virtual void UpdateView() = 0;
		virtual void UpdateViewprojection();
	private:
		// Base vectors
		virtual glm::vec3 Up() const;
		virtual glm::vec3 Right() const;
		virtual glm::vec3 Direction() const;
		virtual glm::vec3 DirectionTo(glm::vec3 target) const;
	};

	class REAL_API OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
	private:
		virtual void UpdateView() override;
	};

	class REAL_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float yfov, float w, float h);
	private:
		virtual void UpdateView() override;
	};
}

#endif //REAL_CAMERA
