// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_TRANSFORM
#define REAL_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "real/core.hpp"

namespace real {
	class REAL_API transform {
	public:
		transform(glm::mat4 transform) : transform_{ transform } {}

		[[nodiscard]] inline glm::mat4 matrix() const noexcept { return transform_; }
	private:
		glm::mat4 transform_ = glm::identity<glm::mat4>();
	};
}

#endif //REAL_TRANSFORM
