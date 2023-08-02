// Copyright (c) 2020 udv. All rights reserved.

#include <glm/glm.hpp>
#include <real/renderer/base_shader.hpp>

#include "real/logger.hpp"
#include "real/renderer.hpp"

namespace Real
{
	Real::Reference<Shader> Shader::Make(std::string filename)
	{
		switch (Renderer::Api().Value())
		{
		case RendererAPI::API::GL:
			return Real::MakeReference<GLShader>(filename);

		default:
		case RendererAPI::API::None:
            REAL_CORE_ERROR("Invalid renderer api: {}",
                            static_cast<int32_t>(RendererAPI::API::None));
			return nullptr;
		}
	}

	Shader::~Shader() = default;

	// Shader library
	void ShaderLibrary::Add(const Real::Reference<Shader>& shader)
	{
		if (shaderMap.contains(shader->Name()))
		{
			return;
		}

		auto& name = shader->Name();
		shaderMap[name] = shader;
	}

	Real::Reference<Shader> ShaderLibrary::Load(const std::string& filename)
	{
		auto shader = Shader::Make(filename);
		Add(shader);
		return shader;
	}

	Real::Reference<Shader> ShaderLibrary::Load(const std::string& name,
			const std::string& filename)
	{
		auto shader = Shader::Make(filename);
		shader->Name(name);
		Add(shader);
		return shader;
	}

	bool ShaderLibrary::Contains(const std::string& name)
	{
		return shaderMap.contains(name);
	}

	Real::Reference<Shader> ShaderLibrary::Get(const std::string& name)
	{
		real_msg_assert(Contains(name), "Shader not found!");
		return shaderMap[name];
	}
}
