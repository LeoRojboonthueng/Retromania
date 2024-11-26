#include "../../include/states/MenuState.hpp"
#include "../../include/states/StateStack.hpp"

MenuState::MenuState(StateStack& stack)
    : State(stack), mSelectedOption(0) {
    if (!mFont.loadFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    mTitle.setFont(mFont);
    mTitle.setString("Retromania");
    mTitle.setCharacterSize(64);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(200, 100);

    mStartOption.setFont(mFont);
    mStartOption.setString("Start Game");
    mStartOption.setCharacterSize(32);
    mStartOption.setFillColor(sf::Color::Green);
    mStartOption.setPosition(200, 250);

    mExitOption.setFont(mFont);
    mExitOption.setString("Exit");
    mExitOption.setCharacterSize(32);
    mExitOption.setFillColor(sf::Color::White);
    mExitOption.setPosition(200, 300);
}

void MenuState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                mSelectedOption = 1 - mSelectedOption;
                mStartOption.setFillColor(mSelectedOption == 0 ? sf::Color::Green : sf::Color::White);
                mExitOption.setFillColor(mSelectedOption == 1 ? sf::Color::Green : sf::Color::White);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (mSelectedOption == 0) {
                    // starts game
					window.clear();
                    mStack.pushState(1);
                }
                else if (mSelectedOption == 1) {
                    // closes
                    window.close();
                }
            }
        }
    }
}

void MenuState::update(sf::Time dt) {
    // Not implemented
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(mTitle);
    window.draw(mStartOption);
    window.draw(mExitOption);
}
