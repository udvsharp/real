// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_SHADER
#define VN_SHADER

#include "version/core.hpp"
#include "version/logger.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// TODO: abstract api
namespace vn {
	class VN_API shader {
	private:
		GLuint id_;

		static void checkhandle_program_error(GLuint id, GLenum action) {
			int success;
			char info_log[512];
			glGetProgramiv(id, action, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, nullptr, info_log);
				VN_CORE_ERROR("GL Shader Program error: {}", info_log);
			}
		}

		static void checkhandle_shader_error(GLuint id, GLenum action) {
			int success;
			char info_log[512];
			glGetShaderiv(id, action, &success);
			if (!success) {
				glGetShaderInfoLog(id, 512, nullptr, info_log);
				VN_CORE_ERROR("GL Shader error: {}", info_log);
			}
		}

		static std::string read_file(const std::string &filepath) {

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

	public:
		shader() : id_{0} {}

		shader(std::string &&vertex_filename, std::string &&fragment_filename) {
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

		void bind() const {
			glUseProgram(id_);
		}

		static void unbind() {
			glUseProgram(0);
		}

	};
}

#endif //VN_SHADER
