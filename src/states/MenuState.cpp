#include "../../include/states/MenuState.hpp"
#include "../../include/states/StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mSelectedOption(0) {
    // Load the menu background image
    if (!mBackgroundTexture.loadFromFile("assets/images/menu_background.png")) {
        std::cerr << "Error: Failed to load menu background image!\n";
    }
    else {
        mBackgroundSprite.setTexture(mBackgroundTexture);
        updateBackgroundScale();
    }

    // Load font
    if (!mFont.loadFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Error: Failed to load font 'Roboto.ttf'. Please ensure it exists in 'assets/fonts/'.\n";
    }

    // Title
    mTitle.setFont(mFont);
    mTitle.setString("Retromania");
    mTitle.setCharacterSize(64);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(200, 100);

    // Menu Options
    mStartOption.setFont(mFont);
    mStartOption.setString("Start Game");
    mStartOption.setCharacterSize(32);
    mStartOption.setFillColor(sf::Color::Green); // Default selected
    mStartOption.setPosition(200, 250);

    mExitOption.setFont(mFont);
    mExitOption.setString("Exit");
    mExitOption.setCharacterSize(32);
    mExitOption.setFillColor(sf::Color::White);
    mExitOption.setPosition(200, 300);

    mSettingsOption.setFont(mFont);
    mSettingsOption.setString("Settings");
    mSettingsOption.setCharacterSize(32);
    mSettingsOption.setFillColor(sf::Color::White);
    mSettingsOption.setPosition(200, 350);
}

void MenuState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                mSelectedOption = (mSelectedOption + 2) % 3;
            }
            if (event.key.code == sf::Keyboard::Down) {
                mSelectedOption = (mSelectedOption + 1) % 3;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (mSelectedOption == 0) {
                    // starts game, window.clear is REQUIRED
                    window.clear();
                    mStack.pushState(1);
                }
                else if (mSelectedOption == 1) {
                    // Close game
                    window.close();
				}
                else if (mSelectedOption == 2) {
                    // settings
                    window.clear();
                    mStack.pushState(3);
                }
            }
            mStartOption.setFillColor(mSelectedOption == 0 ? sf::Color::Green : sf::Color::White);
            mExitOption.setFillColor(mSelectedOption == 1 ? sf::Color::Green : sf::Color::White);
            mSettingsOption.setFillColor(mSelectedOption == 2 ? sf::Color::Green : sf::Color::White);
        }
    }
}

void MenuState::update(sf::Time dt) {
    // Placeholder for future animations or transitions
}

void MenuState::render(sf::RenderWindow& window) {
    // Draw the background
    window.draw(mBackgroundSprite);

    // Draw menu elements
    window.draw(mTitle);
    window.draw(mStartOption);
    window.draw(mExitOption);
	window.draw(mSettingsOption);
}

void MenuState::updateBackgroundScale() {
    sf::Vector2u windowSize = mWindow.getSize();
    sf::Vector2u textureSize = mBackgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    mBackgroundSprite.setScale(scaleX, scaleY);
}