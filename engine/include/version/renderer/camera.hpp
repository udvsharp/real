// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_CAMERA
#define VN_CAMERA

#include <glm/glm.hpp>

#include "version/core.hpp"

namespace vn {
	class VN_API camera {
	public:
		[[nodiscard]] virtual glm::vec3 position() const noexcept = 0;
		virtual void position(glm::vec3 position) noexcept = 0;
		[[nodiscard]] virtual glm::mat4 projection() const noexcept = 0;
		virtual void projection(glm::mat4 projection) noexcept = 0;
		[[nodiscard]] virtual glm::mat4 view() const noexcept = 0;
		[[nodiscard]] virtual glm::mat4 viewprojection() const noexcept = 0;
		[[nodiscard]] virtual float rotation() const noexcept = 0;
		virtual void rotation(float rotation) noexcept = 0;
	};

	class VN_API camera_orthographic : public camera {
	private:
		glm::mat4 view_;
		glm::mat4 projection_;

		glm::mat4 cache_viewprojection_;

		// TODO: migrate to quaternions
		float rotation_ = 0.0f;
		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f, };
	private:
		void update_view();
		void update_viewprojection();
		void update();
	public:
		camera_orthographic(float left, float right, float bottom, float top);

		[[nodiscard]] glm::vec3 position() const noexcept override { return position_; }
		void position(glm::vec3 position) noexcept override { position_ = position; update(); }

		[[nodiscard]] glm::mat4 projection() const noexcept override { return projection_; }
		void projection(glm::mat4 projection) noexcept override { projection_ = projection; update(); }

		[[nodiscard]] glm::mat4 view() const noexcept override { return view_; }
		[[nodiscard]] glm::mat4 viewprojection() const noexcept override { return cache_viewprojection_; }

		[[nodiscard]] float rotation() const noexcept override { return rotation_; }
		void rotation(float rotation) noexcept override { rotation_ = rotation; update(); }

	};

	class VN_API camera_perspective : public camera {

		glm::mat4 view_;
		glm::mat4 projection_;

		glm::mat4 cache_viewprojection_;

		// TODO: migrate to quaternions
		float rotation_ = 0.0f;
		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f, };
	private:
		void update_view();
		void update_viewprojection();
		void update();
	public:
		camera_perspective(float yfov, float w, float h);

		[[nodiscard]] glm::vec3 position() const noexcept override { return position_; }
		void position(glm::vec3 position) noexcept override { position_ = position; update(); }

		[[nodiscard]] glm::mat4 projection() const noexcept override { return projection_; }
		void projection(glm::mat4 projection) noexcept override { projection_ = projection; update(); }

		[[nodiscard]] glm::mat4 view() const noexcept override { return view_; }
		[[nodiscard]] glm::mat4 viewprojection() const noexcept override { return cache_viewprojection_; }

		[[nodiscard]] float rotation() const noexcept override { return rotation_; }
		void rotation(float rotation) noexcept override { rotation_ = rotation; update(); }

	};
}

#endif //VN_CAMERA