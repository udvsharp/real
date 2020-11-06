// Copyright (c) 2020 udv. All rights reserved.



#include <glm/gtc/type_ptr.hpp>

#include "real/api/gl/gl_conversions.hpp"
#include "real/api/gl/gl_shader.hpp"
#include "real/logger.hpp"

#define SYM_EOL "\r\n"

namespace Real
{

	GLShader::GLShader(std::string filename)
			:programId { 0 }, shaders {}
	{
		programId = glCreateProgram();
		auto start = filename.find_last_of("/\\");
		start = (start == std::string::npos) ? 0 : start + 1;
		auto end = filename.rfind(".");
		auto size = end == std::string::npos ? filename.size() - start : end - start;
		shaderName = filename.substr(start, size);

		std::string sources = ReadFile(filename);
		Preprocess(sources);
		const auto& shader_srcs = Split(sources);
		Compile(shader_srcs);
		Link();
	}

	void GLShader::Bind() const
	{
		glUseProgram(programId);
	}

	void GLShader::Unbind() const
	{
		glUseProgram(0);
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(programId);
	}

	// region Uniforms
	// IMP: migrate to "uniform" form
	// TODO: read uniforms from shader source code

	GLint GLShader::LocationOf(const std::string& name) const
	{
		if (uniformLocationsCache.find(name) != uniformLocationsCache.end())
		{
			return uniformLocationsCache[name];
		}

		GLint location = glGetUniformLocation(programId, name.c_str());
		uniformLocationsCache[name] = location;
		return location;
	}

	void GLShader::UniformFloat(const std::string& name, glm::f32 value)
	{
		GLint location = LocationOf(name);
		glUniform1fv(location, 1, &value);
	}

	void GLShader::UniformFloat(const std::string& name, const glm::fvec2& value)
	{
		GLint location = LocationOf(name);
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void GLShader::UniformFloat(const std::string& name, const glm::fvec3& value)
	{
		GLint location = LocationOf(name);
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void GLShader::UniformFloat(const std::string& name, const glm::fvec4& value)
	{
		GLint location = LocationOf(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void GLShader::UniformMatrix(const std::string& name, const glm::fmat3& matrix)
	{
		GLint location = LocationOf(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::UniformMatrix(const std::string& name, const glm::fmat4& matrix)
	{
		GLint location = LocationOf(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::UniformInt(const std::string& name, glm::int32 value)
	{
		GLint location = LocationOf(name);
		glUniform1iv(location, 1, &value);
	}

	void GLShader::UniformInt(const std::string& name, const glm::ivec2& value)
	{
		GLint location = LocationOf(name);
		glUniform2iv(location, 1, glm::value_ptr(value));
	}

	void GLShader::UniformInt(const std::string& name, const glm::ivec3& value)
	{
		GLint location = LocationOf(name);
		glUniform3iv(location, 1, glm::value_ptr(value));
	}

	void GLShader::UniformInt(const std::string& name, const glm::ivec4& value)
	{
		GLint location = LocationOf(name);
		glUniform3iv(location, 1, glm::value_ptr(value));
	}
	// endregion

	//region Helpers
	void GLShader::Preprocess(std::string& source) const
	{
		// TODO: add preprocessing step
	}

	std::unordered_map<GLenum, std::string>
	GLShader::Split(const std::string& source) const
	{
		real_msg_assert(count < shaders.size(), "Reached max shaders count!");
		std::unordered_map<GLenum, std::string> shader_sources;

		const char* token_type = "#shader";
		auto pos = source.find(token_type);
		while (pos != std::string::npos)
		{
			auto eol = source.find_first_of(SYM_EOL, pos);
			real_msg_assert(eol != std::string::npos, GL_SYNTAX_ERROR_MESSAGE);
			auto begin = pos + std::strlen(token_type) + 1;
			std::string typestr = source.substr(begin, eol - begin);

			GLenum type = GLShaderTypeFrom(typestr);
			real_msg_assert(type, "Invalid shader type specified");

			auto shader_code_start = source.find_first_not_of(SYM_EOL, eol);
			real_msg_assert(shader_code_start != std::string::npos,
					GL_SYNTAX_ERROR_MESSAGE);
			pos = source.find(token_type, shader_code_start);

			shader_sources[type] = (pos == std::string::npos)
								   ? source.substr(shader_code_start)
								   : source.substr(shader_code_start,
							pos - shader_code_start);
		}

		return shader_sources;
	}

	void GLShader::Compile(
			const std::unordered_map<GLenum, std::string>& shader_srcs)
	{
		for (auto it = shader_srcs.begin(); it != shader_srcs.end(); ++it)
		{
			auto type = it->first;
			auto src = it->second;
			const GLchar* const source_buffer = src.c_str();

			GLuint shader_id;
			shader_id = glCreateShader(type);
			glShaderSource(shader_id, 1, &source_buffer, nullptr);
			glCompileShader(shader_id);
			CheckHandleShaderError(shader_id, GL_COMPILE_STATUS);
			shaders[count++] = shader_id;
		}
	}

	void GLShader::Link() const
	{
		for (size_t i = 0; i < count; ++i)
		{
			glAttachShader(programId, shaders[i]);
		}

		glLinkProgram(programId);
		CheckHandleProgramError(programId, GL_LINK_STATUS);

		for (size_t i = 0; i < count; ++i)
		{
			glDeleteShader(shaders[i]);
		}
	}

	std::string GLShader::ReadFile(const std::string& filepath)
	{

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			int32_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				REAL_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			REAL_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	void GLShader::CheckHandleShaderError(GLuint id, GLenum action)
	{
		int success;
		char info_log[512];
		glGetShaderiv(id, action, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, nullptr, info_log);
			REAL_CORE_ERROR("GL Shader error: {}", info_log);
		}
	}

	void GLShader::CheckHandleProgramError(GLuint id, GLenum action)
	{
		int success;
		char info_log[512];
		glGetProgramiv(id, action, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, nullptr, info_log);
			REAL_CORE_ERROR("GL Shader Program error: {}", info_log);
		}

	}
	//endregion
}
