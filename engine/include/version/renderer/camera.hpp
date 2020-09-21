// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_CAMERA
#define VN_CAMERA

#include <glm/glm.hpp>

#include "version/core.hpp"

namespace vn {
	class VN_API camera_orthographic {
	private:
		glm::mat4 view_;
		glm::mat4 projection_;

		glm::mat4 cache_viewprojection_;

		float rotation_ = 0.0f;
		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f, };
	private:
		void update_view();
		void update_viewprojection();
		void update();
	public:
		camera_orthographic(float left, float right, float bottom, float top);

		[[nodiscard]] glm::vec3 position() const noexcept { return position_; }
		void position(glm::vec3 position) noexcept { position_ = position; update(); }

		[[nodiscard]] glm::mat4 projection() const noexcept { return projection_; }
		void projection(glm::mat4 projection) noexcept { projection_ = projection; update(); }

		[[nodiscard]] glm::mat4 view() const noexcept { return view_; }
		[[nodiscard]] glm::mat4 viewprojection() const noexcept { return cache_viewprojection_; }

		[[nodiscard]] float rotation() const noexcept { return rotation_; }
		void rotation(float rotation) noexcept { rotation_ = rotation; update(); }

	};
}

#endif //VN_CAMERA
