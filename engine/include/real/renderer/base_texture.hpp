// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_BASE_TEXTURE
#define REAL_BASE_TEXTURE

#include "real/core.hpp"

namespace Real {
	class REAL_API Texture {
	public:
		~Texture();

		virtual void Init() = 0;

		virtual texture_dimension_t Width() const = 0;
		virtual texture_dimension_t Height() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class REAL_API Texture2D : public Texture {
	public:
		~Texture2D();
	public:
		static Real::Reference<Texture2D> Make(const std::string &path);
	};
}

#endif //REAL_BASE_TEXTURE
