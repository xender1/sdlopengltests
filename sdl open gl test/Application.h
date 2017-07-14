#pragma once

#include <stack>
#include <memory>

#include "GameState.h"


class Application
{
public:
	Application();
	~Application();
	
	void runMainGameLoop();

	void pushState(std::unique_ptr<State::GameState> state);
	void popState();

private:
	std::stack<std::unique_ptr<State::GameState>> m_states;

};

