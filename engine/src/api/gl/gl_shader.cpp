// Copyright (c) 2020 udv. All rights reserved.

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "real/api/gl/gl_conversions.hpp"
#include "real/api/gl/gl_shader.hpp"
#include "real/logger.hpp"

namespace real {

	gl_shader::gl_shader(std::string filename) : program_id_{ 0 }, shaders_{} {
		program_id_ = glCreateProgram();
		auto start = filename.find_last_of("/\\");
		start = (start == std::string::npos) ? 0 : start + 1;
		auto end = filename.rfind(".");
		auto count = end == std::string::npos ? filename.size() - start : end - start;
		name_ = filename.substr(start, count);

		std::string sources = read_file(filename);
		preprocess(sources);
		const auto &shader_srcs = split(sources);
		compile(shader_srcs);
		link();
	}

	void gl_shader::bind() const {
		glUseProgram(program_id_);
	}

	void gl_shader::unbind() const {
		glUseProgram(0);
	}

	gl_shader::~gl_shader() {
		glDeleteProgram(program_id_);
	}

	// region Uniforms
	// IMP: migrate to "uniform" form
	// TODO: read uniforms from shader source code

	GLint gl_shader::location_of(const std::string &name) const {
		if (uniform_locations_cache_.find(name) != uniform_locations_cache_.end()) {
			return uniform_locations_cache_[name];
		}

		GLint location = glGetUniformLocation(program_id_, name.c_str());
		uniform_locations_cache_[name] = location;
		return location;
	}

	void gl_shader::uniform_float(const std::string &name, glm::f32 value) {
		GLint location = location_of(name);
		glUniform1fv(location, 1, &value);
	}

	void gl_shader::uniform_float(const std::string &name, const glm::fvec2 &value) {
		GLint location = location_of(name);
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void gl_shader::uniform_float(const std::string &name, const glm::fvec3 &value) {
		GLint location = location_of(name);
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void gl_shader::uniform_float(const std::string &name, const glm::fvec4 &value) {
		GLint location = location_of(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void gl_shader::uniform_matrix(const std::string &name, const glm::fmat3 &matrix) {
		GLint location = location_of(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void gl_shader::uniform_matrix(const std::string &name, const glm::fmat4 &matrix) {
		GLint location = location_of(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void gl_shader::uniform_int(const std::string &name, glm::int32 value) {
		GLint location = location_of(name);
		glUniform1iv(location, 1, &value);
	}

	void gl_shader::uniform_int(const std::string &name, const glm::ivec2 &value) {
		GLint location = location_of(name);
		glUniform2iv(location, 1, glm::value_ptr(value));
	}

	void gl_shader::uniform_int(const std::string &name, const glm::ivec3 &value) {
		GLint location = location_of(name);
		glUniform3iv(location, 1, glm::value_ptr(value));
	}

	void gl_shader::uniform_int(const std::string &name, const glm::ivec4 &value) {
		GLint location = location_of(name);
		glUniform3iv(location, 1, glm::value_ptr(value));
	}
	// endregion

	//region Helpers
	void gl_shader::preprocess(std::string &source) const {
		// TODO: add preprocessing step
	}

	std::unordered_map<GLenum, std::string>
	gl_shader::split(const std::string &source) const {
		real_assert(count_ < shaders_.size(), "Reached max shaders count!");
		std::unordered_map<GLenum, std::string> shader_sources;

		const char *token_type = "#shader";
		auto pos = source.find(token_type);
		while (pos != std::string::npos) {
			auto eol = source.find_first_of(SYM_EOL, pos);
			real_assert(eol != std::string::npos, GL_SYNTAX_ERROR_MESSAGE);
			auto begin = pos + std::strlen(token_type) + 1;
			std::string typestr = source.substr(begin, eol - begin);

			GLenum type = gl_shader_type_from(typestr);
			real_assert(type, "Invalid shader type specified");

			auto shader_code_start = source.find_first_not_of(SYM_EOL, eol);
			real_assert(shader_code_start != std::string::npos, GL_SYNTAX_ERROR_MESSAGE);
			pos = source.find(token_type, shader_code_start);

			shader_sources[type] = (pos == std::string::npos)
			                       ? source.substr(shader_code_start)
			                       : source.substr(shader_code_start,
			                                       pos - shader_code_start);
		}

		return shader_sources;
	}

	void gl_shader::compile(
			const std::unordered_map<GLenum, std::string> &shader_srcs) {
		for (auto it = shader_srcs.begin(); it != shader_srcs.end(); ++it) {
			auto type = it->first;
			auto src = it->second;
			const GLchar *const source_buffer = src.c_str();

			GLuint shader_id;
			shader_id = glCreateShader(type);
			glShaderSource(shader_id, 1, &source_buffer, nullptr);
			glCompileShader(shader_id);
			checkhandle_shader_error(shader_id, GL_COMPILE_STATUS);
			shaders_[count_++] = shader_id;
		}
	}

	void gl_shader::link() const {
		for (size_t i = 0; i < count_; ++i) {
			glAttachShader(program_id_, shaders_[i]);
		}

		glLinkProgram(program_id_);
		checkhandle_program_error(program_id_, GL_LINK_STATUS);

		for (size_t i = 0; i < count_; ++i) {
			glDeleteShader(shaders_[i]);
		}
	}

	std::string gl_shader::read_file(const std::string &filepath) {

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			int32_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			} else {
				REAL_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		} else {
			REAL_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	void gl_shader::checkhandle_shader_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetShaderiv(id, action, &success);
		if (!success) {
			glGetShaderInfoLog(id, 512, nullptr, info_log);
			REAL_CORE_ERROR("GL Shader error: {}", info_log);
		}
	}

	void gl_shader::checkhandle_program_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetProgramiv(id, action, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, nullptr, info_log);
			REAL_CORE_ERROR("GL Shader Program error: {}", info_log);
		}

	}
	//endregion
}
