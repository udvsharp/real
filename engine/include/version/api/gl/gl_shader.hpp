// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_SHADER
#define VN_GL_SHADER

#include "version/core.hpp"
#include "version/renderer/base_shader.hpp"
#include "version/api/gl/gl_headers.hpp"

namespace vn {
	class VN_API gl_shader : public vn::shader {
	public:
		gl_shader();

		void add_shader(int64_t type, const std::string& filename) override;
		void link() override;

		//region Uniforms
		void uniform(const std::string &name, const glm::mat4 &matrix) override;
		void uniform(const std::string &name, const glm::vec4 &vector) override;
		//endregion

		void bind() const override;
		void unbind() const override;
	private:
		//region Helpers
		static std::string read_file(const std::string &filepath);

		static void checkhandle_program_error(GLuint id, GLenum action);
		static void checkhandle_shader_error(GLuint id, GLenum action);
		//endregion
	private:
		GLuint program_id_;
		std::vector<GLuint> shaders_;
	};
}

#endif //VN_GL_SHADER
