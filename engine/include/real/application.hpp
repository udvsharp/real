// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_APPLICATION
#define REAL_APPLICATION

#include <memory>

#include "real/event.hpp"
#include "real/core.hpp"
#include "real/window.hpp"
#include "real/input.hpp"
#include "real/layer_stack.hpp"
#include "real/renderer.hpp"
#include "real/time.hpp"
#include "real/util/singleton.hpp"

namespace Real
{
	class REAL_API SINGLETON(Application)
	{
	public:
		explicit Application(std::string name = REAL_APPLICATION_DEFAULT_NAME);
		virtual ~Application();

		[[nodiscard]] LayerStack& Layers() noexcept
		{ return this->layerStack; }
		[[nodiscard]] Window& Window() const noexcept
		{ return *(this->window); }

		double Time() const;
		void Init();
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	protected:
		virtual void Update(Timestep ts);
		virtual void OnEvent(Event& e);
	private:
		void OnWindowClose(WindowClosedEvent& event);
	private:
		ImGUILayer* imGUILayer;

		std::string name;

		Real::Scope<Real::Window> window;
		Real::Scope<Real::Input> input;

		LayerStack layerStack;

		bool isRunning { true };

		float frametime = 0.0f;
	};

	// To be defined in client
	extern Real::Scope<Real::Application> Make();
}

#endif //REAL_APPLICATION
