// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_BASE_TEXTURE
#define REAL_BASE_TEXTURE

#include "real/core.hpp"

namespace real {
	class REAL_API texture {
	public:
		~texture();

		virtual void init() = 0;

		virtual texture_dimension_t width() const = 0;
		virtual texture_dimension_t height() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;
	};

	class REAL_API texture2d : public texture {
	public:
		~texture2d();
	public:
		static real::reference<texture2d> make(const std::string& path);
	};
}

#endif //REAL_BASE_TEXTURE
