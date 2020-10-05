// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_VERTEX_ARRAY
#define REAL_VERTEX_ARRAY

#include <memory>
#include <vector>

#include "real/core.hpp"

namespace real {
	class vertex_buffer;
	class index_buffer;

	class REAL_API vertex_array {
	private:
	public:
		virtual ~vertex_array();

		[[nodiscard]] virtual const std::vector<std::shared_ptr<real::vertex_buffer>>& vertex_buffers() const = 0;
		[[nodiscard]] virtual const std::vector<std::shared_ptr<real::index_buffer>>& index_buffers() const = 0;

		virtual void add_vertex_buffer(const std::shared_ptr<real::vertex_buffer>& buffer) = 0;
		virtual void add_index_buffer(const std::shared_ptr<real::index_buffer>& buffer) = 0;

		virtual int count() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	public:
		static vertex_array *make();
	};
}

#endif //REAL_VERTEX_ARRAY
