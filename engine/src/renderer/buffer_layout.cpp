// Copyright (c) 2020 udv. All rights reserved.

#include "version/renderer/buffer_layout.hpp"

namespace vn {
	buffer_layout::buffer_layout(std::initializer_list<vertex_attribute> attributes)
			: attributes_{attributes} {
		calculate_params();
	}

	buffer_layout::buffer_layout()
		: attributes_{} {

	}

	void buffer_layout::calculate_params() {
		unsigned int offset = 0;

		for (auto& a : attributes_) {
			a.offset = offset;
			offset += a.size;

			stride_ += a.size;
		}
	}
}
