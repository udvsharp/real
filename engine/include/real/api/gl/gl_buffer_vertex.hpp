// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_VERTEX
#define REAL_GL_BUFFER_VERTEX

#include <memory>

#include "real/core.hpp"
#include "real/renderer/buffer_vertex.hpp"

namespace real {
	class REAL_API gl_vertex_buffer : public vertex_buffer {
	private:
		renderer_id_t renderer_id_;
		buffer_layout layout_;
		std::shared_ptr<real::vertex_array> vertex_array_;
	public:
		gl_vertex_buffer(float* data, unsigned int size);
		virtual ~gl_vertex_buffer();

		[[nodiscard]] virtual const std::shared_ptr<real::vertex_array> & vertex_array() const override { return vertex_array_; };
		[[nodiscard]] virtual const buffer_layout &layout() const override { return layout_; };

		virtual void layout(std::initializer_list<vertex_attribute> attributes) override;
		virtual void link_to(const std::shared_ptr<real::vertex_array> &vertex_array) override;

		virtual void bind() const override;
		virtual void unbind() const override;
	};
}

#endif //REAL_GL_BUFFER_VERTEX
