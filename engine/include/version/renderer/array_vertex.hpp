// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_VERTEX_ARRAY
#define VN_VERTEX_ARRAY

#include <memory>
#include <vector>

#include "version/core.hpp"

namespace vn {
	class vertex_buffer;
	class index_buffer;

	class VN_API vertex_array {
	private:
	public:
		virtual ~vertex_array();

		[[nodiscard]] virtual const std::vector<std::shared_ptr<vn::vertex_buffer>>& vertex_buffers() const = 0;
		[[nodiscard]] virtual const std::vector<std::shared_ptr<vn::index_buffer>>& index_buffers() const = 0;

		virtual void add_vertex_buffer(const std::shared_ptr<vn::vertex_buffer>& buffer) = 0;
		virtual void add_index_buffer(const std::shared_ptr<vn::index_buffer>& buffer) = 0;

		virtual int count() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	public:
		static vertex_array *make();
	};
}

#endif //VN_VERTEX_ARRAY
