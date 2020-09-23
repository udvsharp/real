// Copyright (c) 2020 udv. All rights reserved.

#include <glm/gtc/type_ptr.hpp>

#include "version/renderer/shader.hpp"

namespace vn {
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

	shader::shader() : id_{0} {

	}

	void shader::uniform(const std::string &name, const glm::mat4 &matrix) {
		GLuint location = glGetUniformLocation(id_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void shader::uniform(const std::string &name, const glm::vec4 &vector) {
		GLuint location = glGetUniformLocation(id_, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}

	shader::shader(std::string &&vertex_filename, std::string &&fragment_filename) {
		//region Vertex shader
		const std::string &v_str = read_file(vertex_filename);
		const GLchar *const v_src_buffer = v_str.c_str();

		GLuint vid;
		vid = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vid, 1, &v_src_buffer, nullptr);
		glCompileShader(vid);
		checkhandle_shader_error(vid, GL_COMPILE_STATUS);
		//endregion

		//region Fragment shader
		const std::string &f_str = read_file(fragment_filename);
		const GLchar *const f_src_buffer = f_str.c_str();

		GLuint fid;
		fid = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fid, 1, &f_src_buffer, nullptr);
		glCompileShader(fid);
		checkhandle_shader_error(fid, GL_COMPILE_STATUS);
		//endregion
		// region Program
		id_ = glCreateProgram();
		glAttachShader(id_, vid);
		glAttachShader(id_, fid);
		glLinkProgram(id_);

		checkhandle_program_error(id_, GL_LINK_STATUS);
		// endregion

		glDeleteShader(vid);
		glDeleteShader(fid);
	}


	void shader::bind() const {
		glUseProgram(id_);
	}

	void shader::unbind() const {
		glUseProgram(0);
	}
}
