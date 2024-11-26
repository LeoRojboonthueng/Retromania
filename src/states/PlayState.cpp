#include "../../include/states/PlayState.hpp"
#include "../../include/states/StateStack.hpp"
#include <iostream>

PlayState::PlayState(StateStack& stack)
    : State(stack), mPlayer() {
}

void PlayState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                // pause (also pauses update and render here)
				mStack.pushState(2);
            }
        }
    }

    mPlayer.handleInput();
}

void PlayState::update(sf::Time dt) {
    mPlayer.update(dt);
}

void PlayState::render(sf::RenderWindow& window) {
    mPlayer.render(window);
}