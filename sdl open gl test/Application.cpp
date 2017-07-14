#include "Application.h"

#include "SDLDisplay.h"
#include "Playing.h"


Application::Application()
{
	pushState(std::make_unique<State::Playing>(*this));
}


Application::~Application()
{
}

void Application::runMainGameLoop()
{
	while (Display::isOpen()) {
		Display::clear();

		m_states.top()->input();
		m_states.top()->update();
		m_states.top()->draw();

		Display::handleEvent();
		Display::render();
	}

	Display::close();
}

void Application::pushState(std::unique_ptr<State::GameState> state)
{
	m_states.push(std::move(state));
}

void Application::popState()
{
	m_states.pop();
}
