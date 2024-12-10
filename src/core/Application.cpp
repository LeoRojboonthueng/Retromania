#include "../../include/core/Application.hpp"
#include "./../include/states/MenuState.hpp"
#include "./../include/states/PlayState.hpp"
#include "../../include/states/PauseState.hpp"
#include "../../include/states/SettingsState.hpp"

Application::Application()
    : mWindow(sf::VideoMode(WindowWidth, WindowHeight), WindowTitle, sf::Style::Close),
    mStateStack(mWindow) {
    mWindow.setFramerateLimit(60);

    mStateStack.registerState<MenuState>(0); // MenuState
    mStateStack.registerState<PlayState>(1); // PlayState
    mStateStack.registerState<PauseState>(2); // PauseState
	mStateStack.registerState<SettingsState>(3); // SettingsState

    mStateStack.pushState(0);
}

void Application::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update(mClock.restart());
        render();
    }
}

void Application::processEvents() {
    mStateStack.handleInput();
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::render() {
    mWindow.clear();
    mStateStack.render();
    mWindow.display();
}

