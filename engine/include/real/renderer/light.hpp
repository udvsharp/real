// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_ENGINE_LIGHT
#define REAL_ENGINE_LIGHT

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "real/core.hpp"

namespace Real
{
	class REAL_API Light
	{
	public:
		Light()
				:Light {
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
		}
		{};

		Light(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& diffuse,
				const glm::vec3& specular)
				:pos { pos }, ambient { ambient }, diffuse { diffuse },
				 specular { specular }, shader {}
		{}

		Light(glm::vec3&& pos, glm::vec3&& ambient, glm::vec3&& diffuse,
				glm::vec3&& specular)
				:pos { pos }, ambient { std::move(ambient) },
				 diffuse { std::move(diffuse) },
				 specular { std::move(specular) }, shader {}
		{}

		Light(glm::vec3 pos, const glm::vec3& ambient, const glm::vec3& diffuse,
				const glm::vec3& specular, const Real::Reference<Real::Shader>& shader)
				:Light { pos, ambient, diffuse, specular }
		{
			this->shader = shader;
			Update();
		}

		Light(glm::vec3 pos, glm::vec3&& ambient, glm::vec3&& diffuse,
				glm::vec3&& specular, const Real::Reference<Real::Shader>& shader)
				:Light { pos, ambient, diffuse, specular }
		{
			this->shader = shader;
			Update();
		}

		const glm::vec3& Pos() const
		{ return pos; }
		float* PosPtr()
		{ return glm::value_ptr(pos); }
		void Pos(const glm::vec3& pos_)
		{ Light::pos = pos_; }

		const glm::vec3& Ambient() const
		{ return ambient; }
		float* AmbientPtr()
		{ return glm::value_ptr(ambient); }
		void Ambient(const glm::vec3& ambient_)
		{ Light::ambient = ambient_; }

		const glm::vec3& Diffuse() const
		{ return diffuse; }
		float* DiffusePtr()
		{ return glm::value_ptr(diffuse); }
		void Diffuse(const glm::vec3& diffuse_)
		{ Light::diffuse = diffuse_; }

		const glm::vec3& Specular() const
		{ return specular; }
		float* SpecularPtr()
		{ return glm::value_ptr(specular); }
		void Specular(const glm::vec3& specular_)
		{ Light::specular = specular_; }

		void Update() {
			shader->Bind();

			shader->UniformFloat("u_Light.position", light->Pos());
			shader->UniformFloat("u_Light.ambient", light->Ambient());
			shader->UniformFloat("u_Light.diffuse", light->Diffuse());
			shader->UniformFloat("u_Light.specular", light->Specular());
		}
	private:
		glm::vec3 pos;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		Real::Reference<Real::Shader> shader;
	};
}

#endif //REAL_ENGINE_LIGHT
