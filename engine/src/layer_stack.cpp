// Copyright (c) 2020 udv. All rights reserved.

#include "version/layer_stack.hpp"

namespace vn {
	layer_stack::layer_stack() : stack_{} {
		layer_insert_ = stack_.begin();
	}

	layer_stack::~layer_stack() {
		for (auto *layer : stack_) {
			delete layer;
		}
	}

	void layer_stack::push_layer(layer *layer) {
		layer_insert_ = stack_.emplace(layer_insert_, layer);
		layer->attach();
	}

	void layer_stack::push_overlay(layer *overlay) {
		stack_.emplace_back(overlay);
		overlay->attach();
	}

	void layer_stack::pop_layer(layer *layer) {
		iterator it = std::find(begin(), end(), layer);
		if (it != stack_.end()) {
			(*it)->detach();
			stack_.erase(it);
			--layer_insert_;
		}
	}

	void layer_stack::pop_overlay(layer *overlay) {
		iterator it = std::find(begin(), end(), overlay);
		if (it != stack_.end()) {
			(*it)->detach();
			stack_.erase(it);
		}
	}
}