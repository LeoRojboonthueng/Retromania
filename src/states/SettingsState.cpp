#include "../../include/states/SettingsState.hpp"
#include "../../include/states/StateStack.hpp"
#include <iostream>

SettingsState::SettingsState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mSelectedOption(0) {
    if (!mFont.loadFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Error: Failed to load font 'Roboto.ttf'. Please ensure it exists in 'assets/fonts/'.\n";
    }

    mTitle.setFont(mFont);
    mTitle.setString("Settings");
    mTitle.setCharacterSize(64);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(200, 100);

    mResolutions = { {800, 600}, {1024, 768}, {1280, 960}, {1440, 1080} };
    mResolutionOption.setFont(mFont);
    mResolutionOption.setCharacterSize(32);
    mResolutionOption.setFillColor(sf::Color::Green);
    mResolutionOption.setPosition(200, 250);
    mResolutionOption.setString("Resolution: 800x600");
}

void SettingsState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                mSelectedOption = (mSelectedOption + 1) % mResolutions.size();
                sf::Vector2u resolution = mResolutions[mSelectedOption];
                mResolutionOption.setString("Resolution: " + std::to_string(resolution.x) + "x" + std::to_string(resolution.y));
            }
            if (event.key.code == sf::Keyboard::Enter) {
                sf::Vector2u resolution = mResolutions[mSelectedOption];
                mWindow.create(sf::VideoMode(resolution.x, resolution.y), "Retromania", sf::Style::Close);

                window.clear();
				mStack.clearStates();
            }
        }
    }
}

void SettingsState::update(sf::Time dt) {
    // Not implemented
}

void SettingsState::render(sf::RenderWindow& window) {
    window.draw(mTitle);
    window.draw(mResolutionOption);
}
