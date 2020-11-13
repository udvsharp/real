// Copyright (c) 2020 udv. All rights reserved.



#include "real/application.hpp"

namespace Real
{

	Application::Application(std::string name)
			:Singleton<Application> {},
			 name { std::move(name) }
	{
		// Setup systems
		WindowProperties props {};
		window = Window::Make(props);
		input = Input::Make();

		window->Init();
		window->EventCallback([this](Event& e)
		{
			Application::OnEvent(e);
		});

		Renderer::Init();

		imGUILayer = new Real::ImGUILayer {};
		PushOverlay(imGUILayer);
	}

	void Application::Init()
	{}

	void Application::Run()
	{
		REAL_CORE_TRACE("Application is running!");

		while (isRunning)
		{
			double time = Real::Time();
			Timestep timestep = time - frametime;
			frametime = time;

			RenderCommand::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();

			for (auto* layer : layerStack)
			{
				layer->Update(timestep);
			}

			imGUILayer->Begin();
			for (auto* layer : layerStack)
			{
				layer->OnImGUIRender();
			}
			imGUILayer->End();

			window->OnUpdate(timestep);
			Update(timestep);
		}

		REAL_CORE_TRACE("Closing application...");
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	void Application::Update(Timestep ts)
	{}

	void Application::OnEvent(Event& e)
	{
		// REAL_CORE_TRACE("Got event: {0}", e);

		EventDispatcher dispatcher { &e };
		dispatcher.Dispatch<WindowClosedEvent>([this](WindowClosedEvent& event) -> bool
		{
			this->OnWindowClose(event);
			return false;
		});

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->HandleEvent(e);
			if (e.IsHandled())
			{
				break;
			}
		}
	}

	double Application::Time() const
	{
		return glfwGetTime();
	}

	void Application::OnWindowClose(WindowClosedEvent& event)
	{
		this->isRunning = false;
	}
}

