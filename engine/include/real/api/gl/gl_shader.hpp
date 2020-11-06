// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_SHADER
#define REAL_GL_SHADER

#include <glm/glm.hpp>

#include "real/core.hpp"
#include "real/renderer/base_shader.hpp"
#include "real/api/gl/gl_headers.hpp"

#define GL_SHADERS_MAX_COUNT SHADERS_MAX_COUNT
#define GL_SHADERS_AVG_COUNT SHADERS_AVG_COUNT

namespace Real
{
	class REAL_API GLShader : public Real::Shader
	{
	public:
		GLShader(std::string filename);
		~GLShader() override;

		// region Uniforms
		// Floats
		void UniformFloat(const std::string& name, glm::f32 value) override;
		void UniformFloat(const std::string& name, const glm::fvec2& value) override;
		void UniformFloat(const std::string& name, const glm::fvec3& value) override;
		void UniformFloat(const std::string& name, const glm::fvec4& value) override;

		// Matrices
		void UniformMatrix(const std::string& name, const glm::fmat3& matrix) override;
		void UniformMatrix(const std::string& name, const glm::fmat4& matrix) override;

		// Ints
		void UniformInt(const std::string& name, glm::int32 value) override;
		void UniformInt(const std::string& name, const glm::ivec2& value) override;
		void UniformInt(const std::string& name, const glm::ivec3& value) override;
		void UniformInt(const std::string& name, const glm::ivec4& value) override;
		// endregion

		const std::string& Name() const override
		{ return this->shaderName; }
		void Name(std::string string) override
		{ this->shaderName = string; }

		void Bind() const override;
		void Unbind() const override;
	private:
		//region Helpers
		static std::string ReadFile(const std::string& filepath);

		void Preprocess(std::string& source) const;
		std::unordered_map<GLenum, std::string> Split(const std::string& source) const;
		void Compile(const std::unordered_map<GLenum, std::string>& shader_srcs);
		void Link() const;

		static void CheckHandleProgramError(GLuint id, GLenum action);
		static void CheckHandleShaderError(GLuint id, GLenum action);
		//endregion

		inline GLint LocationOf(const std::string& name) const;
	private:
		GLuint programId;
		std::string shaderName;

		size_t count = 0;
		std::array<GLuint, GL_SHADERS_MAX_COUNT> shaders;

		mutable std::unordered_map<std::string, GLint> uniformLocationsCache;
	};
}

#endif //REAL_GL_SHADER
