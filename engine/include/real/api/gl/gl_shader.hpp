// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_SHADER
#define REAL_GL_SHADER

#include <glm/glm.hpp>

#include "real/core.hpp"
#include "real/renderer/base_shader.hpp"
#include "real/api/gl/gl_headers.hpp"

#define GL_SHADERS_MAX_COUNT SHADERS_MAX_COUNT
#define GL_SHADERS_AVG_COUNT SHADERS_AVG_COUNT

namespace real {
	class REAL_API gl_shader : public real::shader {
	public:
		gl_shader(std::string filename);
		~gl_shader() override;

		// region Uniforms
		// Floats
		void uniform_float(const std::string &name, glm::f32 value) override;
		void uniform_float(const std::string &name, const glm::fvec2 &value) override;
		void uniform_float(const std::string &name, const glm::fvec3 &value) override;
		void uniform_float(const std::string &name, const glm::fvec4 &value) override;
		void uniform_matrix(const std::string &name, const glm::fmat3 &matrix) override;
		void uniform_matrix(const std::string &name, const glm::fmat4 &matrix) override;

		// Ints
		void uniform_int(const std::string &name, glm::int32 value) override;
		void uniform_int(const std::string &name, const glm::ivec2 &value) override;
		void uniform_int(const std::string &name, const glm::ivec3 &value) override;
		void uniform_int(const std::string &name, const glm::ivec4 &value) override;
		// endregion

		const std::string &name() const override { return name_; }
		void name(std::string name) override { name_ = name; }

		void bind() const override;
		void unbind() const override;
	private:
		//region Helpers
		static std::string read_file(const std::string &filepath);

		void preprocess(std::string &source) const;
		std::unordered_map<GLenum, std::string> split(const std::string &source) const;
		void compile(const std::unordered_map<GLenum, std::string> &shader_srcs);
		void link() const;

		static void checkhandle_program_error(GLuint id, GLenum action);
		static void checkhandle_shader_error(GLuint id, GLenum action);
		//endregion

		inline GLint location_of(const std::string &name) const;
	private:
		GLuint program_id_;
		std::string name_;

		size_t count_ = 0;
		std::array<GLuint, GL_SHADERS_MAX_COUNT> shaders_;

		mutable std::unordered_map<std::string, GLint> uniform_locations_cache_;
	};
}

#endif //REAL_GL_SHADER
