// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_CAMERA
#define REAL_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "real/core.hpp"

namespace real {
	class REAL_API camera {
	protected:
		glm::mat4 view_ = glm::identity<glm::mat4>();
		glm::mat4 projection_ = glm::identity<glm::mat4>();

		glm::mat4 cache_viewprojection_ = glm::identity<glm::mat4>();

		// TODO: migrate to quaternions
		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f, };
		glm::vec3 direction_ = { 0.0f, 0.0f, 0.0f, };
	public:
		camera(const glm::mat4 &projection, glm::vec3 position = { 0.0f, 0.0f, 0.0f, },
		       glm::vec3 direction = { 0.0f, 0.0f, 0.0f, });

		virtual void init();

		[[nodiscard]] virtual glm::vec3 position() const noexcept { return position_; };
		virtual void position(glm::vec3 position) noexcept {
			position_ = position;
			update();
		};

		[[nodiscard]] glm::mat4 projection() const noexcept { return projection_; };
		virtual void projection(glm::mat4 projection) noexcept {
			projection_ = projection;
			update_viewprojection();
		};

		[[nodiscard]] virtual glm::mat4 view() const noexcept { return view_; };
		[[nodiscard]] virtual glm::mat4 viewprojection() const noexcept { return cache_viewprojection_; };

		virtual void look_at(glm::vec3 target);
	protected:
		virtual void update();
		virtual void update_view() = 0;
		virtual void update_viewprojection();
	private:
		// Base vectors
		virtual glm::vec3 up() const;
		virtual glm::vec3 right() const;
		virtual glm::vec3 direction() const;
		virtual glm::vec3 direction_to(glm::vec3 target) const;
	};

	class REAL_API camera_orthographic : public camera {
	public:
		camera_orthographic(float left, float right, float bottom, float top);
	private:
		virtual void update_view() override;
	};

	class REAL_API camera_perspective : public camera {
	public:
		camera_perspective(float yfov, float w, float h);
	private:
		virtual void update_view() override;
	};
}

#endif //REAL_CAMERA
