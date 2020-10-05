// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_STACK
#define REAL_LAYER_STACK

#include "real/core.hpp"
#include "real/layer.hpp"

namespace real {
	class REAL_API layer_stack {
		using container = std::vector<layer*>;
		using iterator = container::iterator;
		using const_iterator = container::const_iterator;
	private:
		// TODO: own vector
		container stack_;
		iterator layer_insert_;
	public:
		layer_stack();
		~layer_stack();

		//region Iterators
		iterator begin() noexcept { return stack_.begin(); };
		const_iterator cbegin() const noexcept { return stack_.begin(); };
		const_iterator begin() const noexcept { return stack_.begin(); };

		iterator end() noexcept { return stack_.end(); };
		const_iterator end() const noexcept { return stack_.end(); };
		const_iterator cend() const noexcept { return stack_.end(); };
		//endregion

		void push_layer(layer* layer);
		void pop_layer(layer* layer);

		void push_overlay(layer* overlay);
		void pop_overlay(layer* overlay);
	};
}

#endif //REAL_LAYER_STACK
