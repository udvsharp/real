// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_BUFFER_LAYOUT
#define REAL_BUFFER_LAYOUT

#include <cstdint>

#include "real/core.hpp"
#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/api/gl/gl_conversions.hpp"

namespace Real
{

	struct VertexAttribute
	{
		shader_data_t type;
		std::string name;
		uint32_t size;
		int64_t offset;
		bool normalized = false;

		VertexAttribute(const shader_data_t& type, std::string name)
				:type { type }, name { std::move(name) }, size { sizeofsdt(type) },
				 offset { 0 }, normalized { false }
		{}

		VertexAttribute(const shader_data_t& type, std::string name, bool normalized)
				:type { type }, name { std::move(name) }, size { sizeofsdt(type) },
				 offset { 0 }, normalized { normalized }
		{}

		VertexAttribute(const shader_data_t& type, std::string name, uint32_t size,
				int64_t offset, bool normalized)
				:type { type }, name { std::move(name) }, size { size },
				 offset { offset },
				 normalized { normalized }
		{}

		[[nodiscard]] inline uint32_t component_count() const noexcept
		{
			switch (type)
			{
			case shader_data_t::vec   :
				return 1;
			case shader_data_t::vec2  :
				return 1 * 2;
			case shader_data_t::vec3  :
				return 1 * 3;
			case shader_data_t::vec4  :
				return 1 * 4;
			case shader_data_t::mat3  :
				return 1 * 3 * 3;
			case shader_data_t::mat4  :
				return 1 * 4 * 4;
			case shader_data_t::ivec  :
				return 1;
			case shader_data_t::ivec2 :
				return 1 * 2;
			case shader_data_t::ivec3 :
				return 1 * 3;
			case shader_data_t::ivec4 :
				return 1 * 4;
			case shader_data_t::bvec  :
				return 1;
			case shader_data_t::bvec2 :
				return 1 * 2;
			case shader_data_t::bvec3 :
				return 1 * 3;
			case shader_data_t::bvec4 :
				return 1 * 4;

			default:
			case shader_data_t::none:
				REAL_CORE_ERROR("Unsupported data type: {}!",
						type);
				return 0;
			}
		}

		[[nodiscard]] inline int32_t api_type() const noexcept
		{
			switch (Renderer::Api().Value())
			{
			case RendererAPI::API::GL:
				return GLTypeFrom(type);

			default:
			case RendererAPI::API::none:
				REAL_CORE_ERROR("Invalid renderer api: {}",
						RendererAPI::API::none);
				return -1;
			}
		}
	};

	class REAL_API BufferLayout
	{
		using container = std::vector<VertexAttribute>;
		using iterator = container::iterator;
		using const_iterator = container::const_iterator;
	private:
		std::vector<VertexAttribute> attributes;

		uint32_t stride = 0;
	public:
		BufferLayout();
		BufferLayout(std::initializer_list<VertexAttribute> attributes);

		//region Iterators
		[[nodiscard]] iterator begin() noexcept
		{ return attributes.begin(); };
		[[nodiscard]] const_iterator
		cbegin() const noexcept
		{ return attributes.begin(); };
		[[nodiscard]] const_iterator
		begin() const noexcept
		{ return attributes.begin(); };

		[[nodiscard]] iterator end() noexcept
		{ return attributes.end(); };
		[[nodiscard]] const_iterator end() const noexcept
		{ return attributes.end(); };
		[[nodiscard]] const_iterator cend() const noexcept
		{ return attributes.end(); };
		//endregion

		[[nodiscard]] inline std::vector<VertexAttribute> Attributes() const
		{ return this->attributes; }
		[[nodiscard]] inline uint32_t Stride() const
		{ return this->stride; }

	private:
		void CalculateParams();
	};
}

#endif //REAL_BUFFER_LAYOUT
