#include "../../include/states/PauseState.hpp"
#include "../../include/states/StateStack.hpp"
#include <iostream>

PauseState::PauseState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mSelectedOption(0) {
    if (!mFont.loadFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    mTitle.setFont(mFont);
    mTitle.setString("Game Paused");
    mTitle.setCharacterSize(64);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(200, 100);

    mResumeOption.setFont(mFont);
    mResumeOption.setString("Resume Game");
    mResumeOption.setCharacterSize(32);
    mResumeOption.setFillColor(sf::Color::Green);
    mResumeOption.setPosition(200, 250);

    mExitOption.setFont(mFont);
    mExitOption.setString("Return to Menu");
    mExitOption.setCharacterSize(32);
    mExitOption.setFillColor(sf::Color::White);
    mExitOption.setPosition(200, 300);
}

void PauseState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
				window.clear();
                mStack.popState();
            }
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                mSelectedOption = 1 - mSelectedOption;
                mResumeOption.setFillColor(mSelectedOption == 0 ? sf::Color::Green : sf::Color::White);
                mExitOption.setFillColor(mSelectedOption == 1 ? sf::Color::Green : sf::Color::White);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (mSelectedOption == 0) {
                    // resume
                    window.clear();
                    mStack.popState();
                }
                else if (mSelectedOption == 1) {
                    // main menu
                    mStack.clearStates();
                }
            }
        }
    }
}

void PauseState::update(sf::Time dt) {

}

void PauseState::render(sf::RenderWindow& window) {
    window.draw(mTitle);
    window.draw(mResumeOption);
	window.draw(mExitOption);
}