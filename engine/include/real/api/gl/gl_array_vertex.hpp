// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_ARRAY_VERTEX
#define REAL_GL_ARRAY_VERTEX

#include "real/core.hpp"
#include "real/renderer/array_vertex.hpp"

namespace real {
	class REAL_API gl_vertex_array : public vertex_array {
	public:
		gl_vertex_array();
		~gl_vertex_array() override;

		[[nodiscard]] virtual const std::vector<real::reference<real::vertex_buffer>> &
		vertex_buffers() const override { return vertex_buffers_; };
		[[nodiscard]] virtual const std::vector<real::reference<real::index_buffer>> &
		index_buffers() const override { return index_buffers_; };

		virtual void
		add_vertex_buffer(const real::reference<real::vertex_buffer> &buffer) override;
		virtual void
		add_index_buffer(const real::reference<real::index_buffer> &buffer) override;

		virtual int32_t count() const override;

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		renderer_id_t renderer_id_;
		uint32_t count_;

		std::vector<real::reference<vertex_buffer>> vertex_buffers_;
		std::vector<real::reference<index_buffer>> index_buffers_;
	};
}

#endif //REAL_GL_ARRAY_VERTEX
