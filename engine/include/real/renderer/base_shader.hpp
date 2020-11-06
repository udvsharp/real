// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_BASE_SHADER
#define REAL_BASE_SHADER

#include "real/core.hpp"

#define GL_SYNTAX_ERROR_MESSAGE "Syntax error"
#define SHADERS_MAX_COUNT 4
#define SHADERS_AVG_COUNT 2

namespace Real {
	// TODO: Iterate over shader API again
	class REAL_API Shader {
	public:
		virtual ~Shader();

		// region Uniforms
		// Floats
		virtual void UniformFloat(const std::string &name, glm::f32 value) = 0;
		virtual void UniformFloat(const std::string &name, const glm::fvec2 &value) = 0;
		virtual void UniformFloat(const std::string &name, const glm::fvec3 &value) = 0;
		virtual void UniformFloat(const std::string &name, const glm::fvec4 &value) = 0;
		virtual void
		UniformMatrix(const std::string &name, const glm::fmat3 &matrix) = 0;
		virtual void
		UniformMatrix(const std::string &name, const glm::fmat4 &matrix) = 0;

		// Ints
		virtual void UniformInt(const std::string &name, glm::int32 value) = 0;
		virtual void UniformInt(const std::string &name, const glm::ivec2 &value) = 0;
		virtual void UniformInt(const std::string &name, const glm::ivec3 &value) = 0;
		virtual void UniformInt(const std::string &name, const glm::ivec4 &value) = 0;
		// endregion

		virtual const std::string &Name() const = 0;
		virtual void Name(std::string name) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	public:
		static Real::Reference<Shader> Make(std::string filename);
	};

	class REAL_API ShaderLibrary {
	public:
		ShaderLibrary() :shaderMap{} {}

		void Add(const Reference <Shader>& shader);
		Real::Reference<Shader> Load(const std::string &filename);
		Real::Reference<Shader>
		Load(const std::string &name, const std::string &filename);

		Real::Reference<Shader> Get(const std::string &name);

		bool Contains(const std::string &name);
	private:
		std::unordered_map<std::string, Real::Reference<Shader>> shaderMap;
	};
}

#endif //REAL_BASE_SHADER
