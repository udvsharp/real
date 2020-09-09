// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_ARRAY_VERTEX
#define VN_GL_ARRAY_VERTEX

#include <memory>
#include <vector>

#include "version/core.hpp"
#include "version/renderer/array_vertex.hpp"

namespace vn {
	class VN_API gl_vertex_array : public vertex_array {
	private:
	public:
		gl_vertex_array();
		virtual ~gl_vertex_array();

		[[nodiscard]] virtual const std::vector<std::shared_ptr<vn::vertex_buffer>>& vertex_buffers() const override { return vertex_buffers_; };
		[[nodiscard]] virtual const std::vector<std::shared_ptr<vn::index_buffer>>& index_buffers() const override { return index_buffers_; };

		virtual void add_vertex_buffer(const std::shared_ptr<vn::vertex_buffer>& buffer) override;
		virtual void add_index_buffer(const std::shared_ptr<vn::index_buffer>& buffer) override;

		virtual int count() const override;

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		renderer_id_t renderer_id_;
		int count_;

		std::vector<std::shared_ptr<vertex_buffer>> vertex_buffers_;
		std::vector<std::shared_ptr<index_buffer>> index_buffers_;
	};
}

#endif //VN_GL_ARRAY_VERTEX
