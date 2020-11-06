// Copyright (c) 2020 udv. All rights reserved.



#include "real/layer/base_layer.hpp"
#include "real/logger.hpp"

namespace Real
{

	void Layer::Attach()
	{
		REAL_CORE_TRACE("Attached layer.");
	}

	void Layer::Detach()
	{
		REAL_CORE_TRACE("Detached layer.");
	}

	void Layer::Update(Timestep ts)
	{

	}

	void Layer::HandleEvent(Event& e)
	{

	}

#ifdef REAL_DEBUG
	Layer::Layer(std::string name)
			:name { std::move(name) }
	{}
#endif
}
