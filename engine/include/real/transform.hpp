// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_TRANSFORM
#define REAL_TRANSFORM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "real/core.hpp"

namespace Real
{
	class REAL_API Transform
	{
	public:
		Transform(glm::mat4 transform)
				:transformMat { transform }
		{}

		[[nodiscard]] glm::mat4 Matrix() const noexcept
		{ return transformMat; }
	private:
		glm::mat4 transformMat = glm::identity<glm::mat4>();
	};
}

#endif //REAL_TRANSFORM
