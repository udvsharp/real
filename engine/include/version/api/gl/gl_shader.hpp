// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_SHADER
#define VN_GL_SHADER

#include <unordered_map>

#include <glm/glm.hpp>

#include "version/core.hpp"
#include "version/renderer/base_shader.hpp"
#include "version/api/gl/gl_headers.hpp"

namespace vn {
	class VN_API gl_shader : public vn::shader {
	public:
		gl_shader();
		virtual ~gl_shader();

		void add_shader(int64_t type, const std::string& filename) override;
		void link() override;

		// region Uniforms
		// Floats
		virtual void uniform_float(const std::string &name, glm::f32 value) override;
		virtual void uniform_float(const std::string &name, const glm::fvec2 &value) override;
		virtual void uniform_float(const std::string &name, const glm::fvec3 &value) override;
		virtual void uniform_float(const std::string &name, const glm::fvec4 &value) override;
		virtual void uniform_matrix(const std::string &name, const glm::fmat3 &matrix) override;
		virtual void uniform_matrix(const std::string &name, const glm::fmat4 &matrix) override;

		// Ints
		virtual void uniform_int(const std::string &name, glm::int32 value) override;
		virtual void uniform_int(const std::string &name, const glm::ivec2 &value) override;
		virtual void uniform_int(const std::string &name, const glm::ivec3 &value) override;
		virtual void uniform_int(const std::string &name, const glm::ivec4 &value) override;
		// endregion

		void bind() const override;
		void unbind() const override;
	private:
		//region Helpers
		static std::string read_file(const std::string &filepath);

		static void checkhandle_program_error(GLuint id, GLenum action);
		static void checkhandle_shader_error(GLuint id, GLenum action);
		//endregion

		inline GLint location_of(const std::string& name) const;
	private:
		GLuint program_id_;
		std::vector<GLuint> shaders_;

		mutable std::unordered_map<std::string, GLint> uniform_locations_cache_;
	};
}

#endif //VN_GL_SHADER
