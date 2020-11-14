// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_ENGINE_MATERIAL
#define REAL_ENGINE_MATERIAL

#include <glm/gtc/type_ptr.hpp>

#include "real/core.hpp"
#include "real/renderer/base_shader.hpp"

namespace Real
{
	// TODO: shader bindings?
	class REAL_API Material
	{
	public:
		Material()
				:Material {
				32.0f,
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
		}
		{};

		Material(float shininess, const glm::vec3& ambient, const glm::vec3& diffuse,
				const glm::vec3& specular)
				:shininess { shininess }, ambient { ambient }, diffuse { diffuse },
				 specular { specular }, shader {}
		{}

		Material(float shininess, glm::vec3&& ambient, glm::vec3&& diffuse,
				glm::vec3&& specular)
				:shininess { shininess }, ambient { std::move(ambient) },
				 diffuse { std::move(diffuse) },
				 specular { std::move(specular) }, shader {}
		{}

		Material(float shininess, const glm::vec3& ambient, const glm::vec3& diffuse,
				const glm::vec3& specular, const Real::Reference<Real::Shader>& shader)
				:Material { shininess, ambient, diffuse, specular }
		{
			this->shader = shader;
			Update();
		}

		Material(float shininess, glm::vec3&& ambient, glm::vec3&& diffuse,
				glm::vec3&& specular, const Real::Reference<Real::Shader>& shader)
				:Material { shininess, ambient, diffuse, specular }
		{
			this->shader = shader;
			Update();
		}

		float Shininess() const
		{ return shininess; }
		float* ShininessPtr()
		{ return &shininess; }
		void Shininess(float shininess_)
		{
			Material::shininess = shininess_;
			shader->Bind();
			shader->UniformFloat("u_Material.shininess", shininess);
		}

		const glm::vec3& Ambient() const
		{ return ambient; }
		float* AmbientPtr()
		{ return glm::value_ptr(ambient); }
		void Ambient(const glm::vec3& ambient_)
		{
			Material::ambient = ambient_;
			shader->Bind();
			shader->UniformFloat("u_Material.ambient", ambient);
		}

		const glm::vec3& Diffuse() const
		{ return diffuse; }
		float* DiffusePtr()
		{ return glm::value_ptr(diffuse); }
		void Diffuse(const glm::vec3& diffuse_)
		{
			Material::diffuse = diffuse_;
			shader->Bind();
			shader->UniformFloat("u_Material.diffuse", diffuse);
		}

		const glm::vec3& Specular() const
		{ return specular; }
		float* SpecularPtr()
		{ return glm::value_ptr(specular); }
		void Specular(const glm::vec3& specular_)
		{
			Material::specular = specular_;
			shader->Bind();
			shader->UniformFloat("u_Material.specular", specular);
		}

		const Real::Reference<Shader>& Shader() const
		{ return shader; }
		void Rebind(const Real::Reference<Real::Shader>& new_shader)
		{
			*this = Real::Material { shininess, ambient, diffuse, specular, new_shader };
		}

		void Update() const
		{
			// TODO: upgrade this
			shader->Bind();
			shader->UniformFloat("u_Material.ambient", ambient);
			shader->UniformFloat("u_Material.diffuse", diffuse);
			shader->UniformFloat("u_Material.specular", specular);
			shader->UniformFloat("u_Material.shininess", shininess);
		}
	private:
		float shininess;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		Real::Reference<Real::Shader> shader;
	};
}

#endif //REAL_ENGINE_MATERIAL
