// Copyright (c) 2020 udv. All rights reserved.

#include "real/layer_stack.hpp"

namespace Real
{
	LayerStack::LayerStack()
			:stack {}, layerInsert { 0 }
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto* layer : stack)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		stack.emplace(stack.begin() + layerInsert++, layer);
		layer->Attach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		stack.emplace_back(overlay);
		overlay->Attach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != stack.end())
		{
			(*it)->Detach();
			stack.erase(it);
			--layerInsert;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(begin(), end(), overlay);
		if (it != stack.end())
		{
			(*it)->Detach();
			stack.erase(it);
		}
	}
}