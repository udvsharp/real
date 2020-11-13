// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_STACK
#define REAL_LAYER_STACK

#include "real/core.hpp"
#include "real/layer.hpp"

namespace Real
{
	class REAL_API LayerStack
	{
		using container = std::vector<Layer*>;
		using iterator = container::iterator;
		using const_iterator = container::const_iterator;
	private:
		// TODO: own vector
		container stack;
		typename container::size_type layerInsert;
	public:
		LayerStack();
		~LayerStack();

		//region Iterators
		iterator begin() noexcept
		{ return stack.begin(); };
		const_iterator cbegin() const noexcept
		{ return stack.begin(); };
		const_iterator begin() const noexcept
		{ return stack.begin(); };

		iterator end() noexcept
		{ return stack.end(); };
		const_iterator end() const noexcept
		{ return stack.end(); };
		const_iterator cend() const noexcept
		{ return stack.end(); };
		//endregion

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);
	};
}

#endif //REAL_LAYER_STACK
