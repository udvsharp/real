// Copyright (c) 2020 udv. All rights reserved.

#include "real/renderer/base_texture.hpp"

#include <memory>

#include "real/renderer.hpp"

namespace Real
{

	// region Texture
	Texture::~Texture() = default;
	// endregion Texture
	// region Texture2D
	Real::Reference<Texture2D> Texture2D::Make(const std::string& path)
	{
		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return Real::MakeReference<GLTexture2D>(path);

		default:
		case RendererAPI::API::none:
			REAL_CORE_ERROR("Invalid renderer api: {}",
					RendererAPI::API::none);
			return nullptr;
		}
	}

	Texture2D::~Texture2D() = default;
	// endregion Texture2d
}
