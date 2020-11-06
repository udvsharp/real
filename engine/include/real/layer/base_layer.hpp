// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_BASE
#define REAL_LAYER_BASE

#include "real/time/timestep.hpp"

#include "real/core.hpp"
#include "real/event.hpp"

namespace Real
{
	class REAL_API Layer
	{
	public:
		Layer() = default;
#ifdef REAL_DEBUG
		explicit Layer(std::string name);
#endif

		virtual void Attach();
		virtual void Detach();
		virtual void Update(Timestep ts);
		virtual void HandleEvent(Event& e);
	private:
#ifdef REAL_DEBUG
		std::string name;
#endif
	};
}

#endif //REAL_LAYER_BASE
