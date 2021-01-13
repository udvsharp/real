// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_ENGINE_LIGHT
#define REAL_ENGINE_LIGHT

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "real/core.hpp"

namespace Real
{
	enum LightType
	{
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOTLIGHT,
		FLASHLIGHT,
	};

	class REAL_API Light
	{
	public:
		// TODO: fix mess ?

		Light()
				:Light {
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
				{ 1.0f, 1.0f, 1.0f, },
		}
		{};

		Light(const glm::vec3& ambient, const glm::vec3& diffuse,
				const glm::vec3& specular)
				:pos { 0.0f, 0.0f, 0.0f, },
				 direction { 0.0f, 0.0f, 0.0f, },
				 ambient { ambient },
				 diffuse { diffuse },
				 specular { specular }
		{}

		Light(glm::vec3&& ambient, glm::vec3&& diffuse,
				glm::vec3&& specular)
				:pos { 0.0f, 0.0f, 0.0f, },
				 direction { 0.0f, 0.0f, 0.0f, },
				 ambient { std::move(ambient) },
				 diffuse { std::move(diffuse) },
				 specular { std::move(specular) }
		{}

		const glm::vec3& Pos() const
		{ return pos; }
		void Pos(const glm::vec3& pos_)
		{ Light::pos = pos_; }

		const glm::vec3& Direction() const
		{ return direction; }
		void Direction(const glm::vec3& dir_)
		{ Light::direction = dir_; }

		const glm::vec3& Ambient() const
		{ return ambient; }
		void Ambient(const glm::vec3& ambient_)
		{ Light::ambient = ambient_; }

		const glm::vec3& Diffuse() const
		{ return diffuse; }
		void Diffuse(const glm::vec3& diffuse_)
		{ Light::diffuse = diffuse_; }

		const glm::vec3& Specular() const
		{ return specular; }
		void Specular(const glm::vec3& specular_)
		{ Light::specular = specular_; }

		// TODO: think about ImGui
	public:
		void ImGUIBegin()
		{
			ImGui::Text("Light");
			ImGui::Separator();
			ImGui::ColorEdit3("Light Ambient", glm::value_ptr(ambient));
			ImGui::ColorEdit3("Light Diffuse", glm::value_ptr(diffuse));
			ImGui::ColorEdit3("Light Specular", glm::value_ptr(specular));
		}

		void ImGUIEnd()
		{
			ImGui::Separator();
		}
	public:
	private:
		// TODO: add transform
		glm::vec3 pos;
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		Real::LightType type;
	};
}

#endif //REAL_ENGINE_LIGHT
