// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_TRANSFORM
#define VN_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "version/core.hpp"

namespace vn {
	class VN_API transform {
	private:
		glm::mat4 transform_ = glm::identity<glm::mat4>();
	public:
		transform(glm::mat4 transform) : transform_{ transform } {}

		[[nodiscard]] inline glm::mat4 matrix() const noexcept { return transform_; }
	};
}

#endif //VN_TRANSFORM
