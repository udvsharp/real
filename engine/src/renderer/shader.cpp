// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/type_ptr.hpp>

#include "version/renderer/shader.hpp"

namespace vn {
	//region Helpers
	std::string shader::read_file(const std::string &filepath) {

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			} else {
				VN_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		} else {
			VN_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	void shader::checkhandle_shader_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetShaderiv(id, action, &success);
		if (!success) {
			glGetShaderInfoLog(id, 512, nullptr, info_log);
			VN_CORE_ERROR("GL Shader error: {}", info_log);
		}
	}

	void shader::checkhandle_program_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetProgramiv(id, action, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, nullptr, info_log);
			VN_CORE_ERROR("GL Shader Program error: {}", info_log);
		}

	}
	//endregion

	shader::shader() : program_id_{0}, shaders_{} {
		shaders_.reserve(2);
		program_id_ = glCreateProgram();
	}

	shader::shader(std::string &&vertex_filename, std::string &&fragment_filename) : shader() {
		add_shader(GL_VERTEX_SHADER, std::move(vertex_filename));
		add_shader(GL_FRAGMENT_SHADER, std::move(fragment_filename));

		program_id_ = glCreateProgram();
	}

	void shader::add_shader(int64_t type, const std::string &filename) {
		const std::string &source = read_file(filename);
		const GLchar *const source_buffer = source.c_str();

		GLuint shader_id;
		shader_id = glCreateShader(type);
		glShaderSource(shader_id, 1, &source_buffer, nullptr);
		glCompileShader(shader_id);
		checkhandle_shader_error(shader_id, GL_COMPILE_STATUS);
		shaders_.push_back(shader_id);
	}

	void shader::link() {
		for (const GLuint& id : shaders_) {
			glAttachShader(program_id_, id);
		}

		glLinkProgram(program_id_);
		checkhandle_program_error(program_id_, GL_LINK_STATUS);

		for (const GLuint& id : shaders_) {
			glDeleteShader(id);
		}
	}

	void shader::bind() const {
		glUseProgram(program_id_);
	}

	void shader::unbind() const {
		glUseProgram(0);
	}

	// region Uniforms

	void shader::uniform(const std::string &name, const glm::mat4 &matrix) {
		GLuint location = glGetUniformLocation(program_id_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void shader::uniform(const std::string &name, const glm::vec4 &vector) {
		GLuint location = glGetUniformLocation(program_id_, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}

	// endregion
}
