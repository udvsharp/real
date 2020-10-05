// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/renderer/base_renderer.hpp"
#include "real/api/gl/gl_buffer_index.hpp"

namespace real {

	index_buffer *index_buffer::make(unsigned int *data, unsigned int size) {

		switch (renderer::api().enumval()) {
			case renderer_api::api::gl:
				return new gl_index_buffer(data, size);

			default:
			case renderer_api::api::none:
				REAL_CORE_ERROR("Invalid renderer api: {}", renderer_api::api::none);
				return nullptr;
		}
	}

	index_buffer::~index_buffer() {}

}
